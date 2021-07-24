#include "ckpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cherenkov {

	static GLenum getShaderType(const std::string& type) {
		if ((type == "vertex") || type == "vert") {
			return GL_VERTEX_SHADER;
		} else if ((type == "fragment") || (type == "frag") || (type == "pixel")) {
			return GL_FRAGMENT_SHADER;
		} else {
			CK_CORE_ERROR("Unknown type: {0}", type);
		}
		return 0;
	}

	std::string getSource(const char* path) {
		CK_PROFILE_FUNCTION();
		std::ifstream file(path, std::ios::in | std::ios::binary);
		if (file) {
		
		} else {
			CK_CORE_ERROR("Failed to load shader @ {0}", path);
		}
		std::string code;

		file.seekg(0, std::ios::end);
		code.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		code.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
		return code;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaders) {
		CK_PROFILE_FUNCTION();
		CK_CORE_ASSERT(shaders.size() <= 5, "Maximum shader limit exceeded!");
		std::array<GLenum, 5> shaderIDs;
		int idx = 0;
		GLuint id = glCreateProgram();
		for (auto& kv : shaders) {
			GLenum type = kv.first;
			const std::string& src = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* source = src.c_str();
			glShaderSource(shader, 1, &source, nullptr);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				CK_CORE_ERROR("{0}", infoLog.data());
				CK_CORE_ASSERT(false, "Shader compilation failed!");
				break;
			}

			glAttachShader(id, shader);
			shaderIDs[idx++] = shader;
		}		

		glLinkProgram(id);

		GLint isLinked = 0;
		glGetProgramiv(id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(id);
			for (auto sID : shaderIDs)
				glDeleteShader(sID);

			CK_CORE_ERROR("{0}", infoLog.data());
			CK_CORE_ASSERT(false, "Shader linking failed!");
			return;
		}

		for (auto sID : shaderIDs) {
			glDetachShader(id, sID);
			glDeleteShader(sID);
		}
		m_ID = id;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::parse(const std::string& src) {
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
			GLenum shaderType = getShaderType(type);
			CK_CORE_ASSERT(shaderType, "Invalid shader type specified");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			CK_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = src.find(typeMarker, nextLinePos);
			shaders[shaderType] = src.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? src.size() - 1 : nextLinePos));
		}
		return shaders;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) : m_Name{name}{
		CK_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = getSource(vertexPath.c_str());
		shaders[GL_FRAGMENT_SHADER] = getSource(fragmentPath.c_str());
		compile(shaders);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)	{
		CK_PROFILE_FUNCTION();
		std::string source = getSource(filepath.c_str());
		auto shaders = parse(source);
		compile(shaders);

		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.') - 1;

		m_Name = filepath.substr(lastSlash, lastDot - lastSlash);
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