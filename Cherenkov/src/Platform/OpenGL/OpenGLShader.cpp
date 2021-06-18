#include "ckpch.h"
#include "OpenGLShader.h"

#include "Cherenkov/Log.h"
#include <glad/glad.h>

namespace Cherenkov {

	std::string getSource(const char* path) {

		std::ifstream file(path);
		std::string code;

		file.seekg(0, std::ios::end);
		code.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		code.assign((std::istreambuf_iterator<char>(file)),	std::istreambuf_iterator<char>());

		return code;
	}

	OpenGLShader::OpenGLShader(const char* vertexPath, const char* fragmentPath) : m_ID{NULL} {
		
		// Read our shaders into the appropriate buffers
		std::string vertexSource = getSource(vertexPath);// Get source code for vertex shader.
		std::string fragmentSource = getSource(fragmentPath);// Get source code for fragment shader.

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			CK_CORE_ERROR("{0}", infoLog.data());
			CK_CORE_ASSERT(false, "Shader (Vertex) compilation failed!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			CK_CORE_ERROR("{0}", infoLog.data());
			CK_CORE_ASSERT(false, "Shader (Fragment) compilation failed!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_ID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);

		// Link our program
		glLinkProgram(m_ID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_ID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CK_CORE_ERROR("{0}", infoLog.data());
			CK_CORE_ASSERT(false, "Shader linking failed!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_ID, vertexShader);
		glDetachShader(m_ID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::bind() const {
		glUseProgram(m_ID);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}
}