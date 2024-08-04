#pragma once

#include "Pixel/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Pixel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& p_Filepath);
		OpenGLShader(const std::string& p_Name, const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& p_Name, int p_Value) override;
		virtual void SetFloat(const std::string& p_Name, float p_Value) override;
		virtual void SetFloat3(const std::string& p_Name, const glm::vec3& p_Value) override;
		virtual void SetFloat4(const std::string& p_Name, const glm::vec4& p_Value) override;
		virtual void SetMat4(const std::string& p_Name, const glm::mat4& p_Value) override;

		inline virtual const std::string& GetName() const override { return m_Name; };

		void UploadUniformInt(const std::string& p_Name, int p_Values) const;

		void UploadUniformFloat(const std::string& p_Name, float p_Values) const;
		void UploadUniformFloat2(const std::string& p_Name, const glm::vec2& p_Values) const;
		void UploadUniformFloat3(const std::string& p_Name, const glm::vec3& p_Values) const;
		void UploadUniformFloat4(const std::string& p_Name, const glm::vec4& p_Values) const;

		void UploadUniformMat3(const std::string& p_Name, const glm::mat3& p_Matrix) const;
		void UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix) const;

	private:
		std::string ReadFile(const std::string& p_Filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& p_Source);
		void Compile(const std::unordered_map<GLenum, std::string>& p_ShaderSources);

		uint32_t m_RendererID = 0;
		std::string m_Name;
	};
}// namespace Pixel#pragma once
