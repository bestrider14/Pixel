#include "pxpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Pixel
{
	OpenGLShader::OpenGLShader(const std::string& p_VertexSrc, const std::string& p_FragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)p_VertexSrc.c_str();
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

			PX_CORE_ERROR("{0}", infoLog.data());
			PX_CORE_ASSERT(false, "Vertex shader compilation failure!")

				return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = p_FragmentSrc.c_str();
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

			PX_CORE_ERROR("{0}", infoLog.data());
			PX_CORE_ASSERT(false, "Fragment shader compilation failure!")

				return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		// Link our program
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PX_CORE_ERROR("{0}", infoLog.data());
			PX_CORE_ASSERT(false, "Shader link failure!")

				return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& p_Name, int p_Values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform1i(location, p_Values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& p_Name, float p_Values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform1f(location, p_Values);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& p_Name, const glm::vec2& p_Values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform2f(location, p_Values.x, p_Values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& p_Name, const glm::vec3& p_Values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform3f(location, p_Values.x, p_Values.y, p_Values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& p_Name, const glm::vec4& p_Values) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform4f(location, p_Values.x, p_Values.y, p_Values.z, p_Values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& p_Name, const glm::mat3& p_Matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix) const
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}
}// namespace Pixel