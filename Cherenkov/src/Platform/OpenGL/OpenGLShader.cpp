#include "ckpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

namespace Cherenkov {

	namespace Utils {
		static GLenum getShaderType(const std::string& type) {
			if ((type == "vertex") || type == "vert") {
				return GL_VERTEX_SHADER;
			}
			else if ((type == "fragment") || (type == "frag") || (type == "pixel")) {
				return GL_FRAGMENT_SHADER;
			}
			else {
				CK_CORE_ERROR("Unknown type: {0}", type);
				return 0;
			}
		}

		static shaderc_shader_kind GLShaderToShaderC(GLenum stage) {
		
			switch (stage) {
			case GL_VERTEX_SHADER:		return shaderc_glsl_vertex_shader;
			case GL_FRAGMENT_SHADER:	return shaderc_glsl_fragment_shader;
			default:					CK_CORE_ASSERT(false); return (shaderc_shader_kind)0;
			}
		}

		static const char* GLShaderToString(GLenum stage) {
			switch (stage) {
			case GL_VERTEX_SHADER:		return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER:	return "GL_FRAGMENT_SHADER";
			default:					CK_CORE_ASSERT(false); return nullptr;
			}
		}

		static const char* getCacheDir()	{ return "assets/cache/shader/opengl"; }

		static void createCacheDir() {
			std::string cacheDir = getCacheDir();
			if (!std::filesystem::exists(cacheDir))	std::filesystem::create_directories(cacheDir);
		}

		static const char* GLShaderCachedGLExtension(uint32_t stage) {
			switch (stage) {
			case GL_VERTEX_SHADER:		return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER:	return ".cached_opengl.frag";
			default:					CK_CORE_ASSERT(false); return "";
			}
		}

		static const char* GLShaderCachedVulkanExtension(uint32_t stage) {
			switch (stage) {
			case GL_VERTEX_SHADER:		return ".cached_vulkan.vert";
			case GL_FRAGMENT_SHADER:	return ".cached_vulkan.frag";
			default:					CK_CORE_ASSERT(false); return "";
			}
		}
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) : m_Name{ name } {
		CK_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = readFile(vertexPath.c_str());
		shaders[GL_FRAGMENT_SHADER] = readFile(fragmentPath.c_str());
		
		compileOrGetVulkanBinaries(shaders);
		compileOrGetOpenGLBinaries();
		createProgram();
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) : m_Filepath{ filepath } {
		CK_PROFILE_FUNCTION();
		Utils::createCacheDir();
		std::string source = readFile(filepath.c_str());
		auto shaders = preProcess(source);

		{
			CK_PROFILE_SCOPE("Shader creation");
			compileOrGetVulkanBinaries(shaders);
			compileOrGetOpenGLBinaries();
			createProgram();
		}

		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.') - 1;
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	std::string OpenGLShader::readFile(const char* path) {
		CK_PROFILE_FUNCTION();
		std::string code;
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (file) {
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			if (size != -1) {
				code.resize(size);
				file.seekg(0, std::ios::beg);
				file.read(&code[0], size);
			}
			else {
				CK_CORE_ERROR("Failed to read from '{0}'.", path);
			}
		}
		else {
			CK_CORE_ERROR("Failed to load shader @ '{0}'", path);
		}

		return code;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& src) {
		CK_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaders;

		const char* typeMarker = "#type";
		size_t markerLen = strlen(typeMarker);
		size_t pos = src.find(typeMarker, 0);
		while (pos != std::string::npos) {
			size_t eol = src.find_first_of("\r\n", pos);
			CK_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + markerLen + 1;
			std::string type = src.substr(begin, eol - begin);
			GLenum shaderType = Utils::getShaderType(type);
			CK_CORE_ASSERT(shaderType, "Invalid shader type specified");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			CK_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = src.find(typeMarker, nextLinePos);
			shaders[shaderType] = (pos == std::string::npos) ? src.substr(nextLinePos) : src.substr(nextLinePos, pos - nextLinePos);
		}
		return shaders;
	}

	void OpenGLShader::compileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaders) {
		CK_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);

		const bool optimise = true;
		if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_performance);
		std::filesystem::path cacheDir = Utils::getCacheDir();
		
		auto& shaderData = m_VulkanSPIRV;
		shaderData.clear();
		for (auto&& [stage, src] : shaders) {
			std::filesystem::path shaderFilepath = m_Filepath;
			std::filesystem::path cachedPath = cacheDir / (shaderFilepath.filename().string() + Utils::GLShaderCachedVulkanExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open()) {
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);
				
				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else {
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(src, Utils::GLShaderToShaderC(stage), m_Filepath.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
					CK_CORE_ERROR(module.GetErrorMessage());
					CK_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open()) {
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}

		for (auto&& [stage, data] : shaderData) reflect(stage, data);
	}

	void OpenGLShader::compileOrGetOpenGLBinaries() {
		auto& shaderData = m_OpenGLSPIRV;
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimise = true;
		if (optimise) options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDir = Utils::getCacheDir();
		shaderData.clear();
		m_OpenGLSource.clear();

		for (auto&& [stage, spirv] : m_VulkanSPIRV) {
			std::filesystem::path shaderFilepath = m_Filepath;
			std::filesystem::path cachePath = cacheDir / (shaderFilepath.filename().string() + Utils::GLShaderCachedGLExtension(stage));

			std::ifstream in(cachePath, std::ios::in | std::ios::binary);
			if (in.is_open()) {
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else {
				spirv_cross::CompilerGLSL	glslCompiler(spirv);
				m_OpenGLSource[stage] = glslCompiler.compile();
				auto& source = m_OpenGLSource[stage];

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderToShaderC(stage), m_Filepath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
					CK_CORE_ERROR(module.GetErrorMessage());
					CK_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachePath, std::ios::out | std::ios::binary);
				if (out.is_open()) {
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}

	}

	void OpenGLShader::createProgram() {
		GLuint program = glCreateProgram();
		std::vector<GLuint> shaderIDs;

		for (auto&& [stage, spirv] : m_OpenGLSPIRV) {
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			CK_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_Filepath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs) glDeleteShader(id);
		}

		for (auto id : shaderIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_ID = program;

	}

	void OpenGLShader::reflect(GLenum stage, const std::vector<uint32_t>& data) {
		spirv_cross::Compiler compiler(data);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		CK_CORE_TRACE("OpenGLShader::reflect - {0} {1}", Utils::GLShaderToString(stage), m_Filepath);
		CK_CORE_TRACE("{0} uniform buffers", resources.uniform_buffers.size());
		CK_CORE_TRACE("{0} resources", resources.sampled_images.size());

		CK_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = bufferType.member_types.size();

			CK_CORE_TRACE("  {0}", resource.name);
			CK_CORE_TRACE("    Size = {0}", bufferSize);
			CK_CORE_TRACE("    Binding = {0}", binding);
			CK_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	OpenGLShader::~OpenGLShader() {
		CK_PROFILE_FUNCTION();
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::bind() const {
		CK_PROFILE_FUNCTION();
		glUseProgram(m_ID);
	}

	void OpenGLShader::unbind() const {
		CK_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::setInt(const std::string& name, int32_t value) {
		CK_PROFILE_FUNCTION();
		uploadUniformInt(name, value);
	}

	void OpenGLShader::setIntArray(const std::string& name, int32_t* values, uint32_t count) {
		CK_PROFILE_FUNCTION();
		uploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::setFloat(const std::string& name, float_t value) {
		CK_PROFILE_FUNCTION();
		uploadUniformFloat(name, value);
	}

	void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& vector) {
		CK_PROFILE_FUNCTION();
		uploadUniformFloat2(name, vector);
	}

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& vector) {
		CK_PROFILE_FUNCTION();
		uploadUniformFloat3(name, vector);
	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& vector) {
		CK_PROFILE_FUNCTION();
		uploadUniformFloat4(name, vector);
	}

	void OpenGLShader::setMat3(const std::string& name, const glm::mat3& matrix) {
		CK_PROFILE_FUNCTION();
		uploadUniformMat3(name, matrix);
	}

	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& matrix) {
		CK_PROFILE_FUNCTION();
		uploadUniformMat4(name, matrix);
	}

	void OpenGLShader::uploadUniformInt(const std::string& id, int32_t value) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform1i(loc, value);
	}

	void OpenGLShader::uploadUniformIntArray(const std::string& id, int32_t* values, uint32_t count) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform1iv(loc, count, values);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& id, const glm::mat3& matrix) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const std::string& id, const glm::mat4& matrix) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformFloat(const std::string& id, float_t value) const	{
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform1f(loc, value);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& id, const glm::vec2& vector) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform2f(loc, vector.x, vector.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& id, const glm::vec3& vector) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform3f(loc, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& id, const glm::vec4& vector) const {
		GLint loc = glGetUniformLocation(m_ID, id.c_str());
		glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
	}
}
