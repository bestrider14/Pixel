#include "pxpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Pixel
{
	static GLenum ShaderTypeFromString(const std::string& p_Type)
	{
		if (p_Type == "vertex")
			return GL_VERTEX_SHADER;
		if (p_Type == "fragment" || p_Type == "pixel")
			return GL_FRAGMENT_SHADER;

		PX_CORE_ASSERT(false, "Unknow shader type!");
		return 0;
	}
	
	OpenGLShader::OpenGLShader(const std::string& p_Filepath)
	{		
		PX_PROFILE_FUNCTION();
		
		std::string source = ReadFile(p_Filepath);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);

		// assets/shaders/Texture.glsl
		auto lastSlash = p_Filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = p_Filepath.rfind('.');
		auto count = lastDot == std::string::npos ? p_Filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = p_Filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& p_Name, const std::string& p_VertexSrc, const std::string& p_FragmentSrc)
		:m_Name(p_Name)
	{
		PX_PROFILE_FUNCTION();
		
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = p_VertexSrc;
		sources[GL_FRAGMENT_SHADER] = p_FragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		PX_PROFILE_FUNCTION();
		
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		PX_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		PX_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& p_Name, int p_Value)
	{
		PX_PROFILE_FUNCTION();

		UploadUniformInt(p_Name, p_Value);
	}

	void OpenGLShader::SetFloat(const std::string& p_Name, float p_Value)
	{
		PX_PROFILE_FUNCTION();

		UploadUniformFloat(p_Name, p_Value);
	}

	void OpenGLShader::SetFloat3(const std::string& p_Name, const glm::vec3& p_Value)
	{
		PX_PROFILE_FUNCTION();

		UploadUniformFloat3(p_Name, p_Value);
	}

	void OpenGLShader::SetFloat4(const std::string& p_Name, const glm::vec4& p_Value)
	{
		PX_PROFILE_FUNCTION();

		UploadUniformFloat4(p_Name, p_Value);
	}

	void OpenGLShader::SetMat4(const std::string& p_Name, const glm::mat4& p_Value)
	{
		PX_PROFILE_FUNCTION();

		UploadUniformMat4(p_Name, p_Value);
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

	std::string OpenGLShader::ReadFile(const std::string& p_Filepath)
	{
		PX_PROFILE_FUNCTION();
		
		std::string result;
		std::ifstream in(p_Filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			PX_CORE_ERROR("Could not open file '{0}'", p_Filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& p_Source)
	{
		PX_PROFILE_FUNCTION();
		
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = p_Source.find(typeToken, 0);
		
		while (pos != std::string::npos)
		{
			size_t eol = p_Source.find_first_of("\r\n", pos);
			PX_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = p_Source.substr(begin, eol - begin);
			PX_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = p_Source.find_first_not_of("\r\n", eol);
			pos = p_Source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = p_Source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? p_Source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& p_ShaderSources)
	{
		PX_PROFILE_FUNCTION();
		
		GLuint program = glCreateProgram();
		PX_CORE_ASSERT(p_ShaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;


		for (auto& kv : p_ShaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = (const GLchar*)source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

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

				PX_CORE_ERROR("{0}", infoLog.data());
				PX_CORE_ASSERT(false, "Shader compilation failure!")
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			PX_CORE_ERROR("{0}", infoLog.data());
			PX_CORE_ASSERT(false, "Shader link failure!")

			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}

}// namespace Pixel