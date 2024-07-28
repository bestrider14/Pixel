#pragma once

#include "Pixel/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Pixel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& p_Name, int p_Values) const;

		void UploadUniformFloat(const std::string& p_Name, float p_Values) const;
		void UploadUniformFloat2(const std::string& p_Name, const glm::vec2& p_Values) const;
		void UploadUniformFloat3(const std::string& p_Name, const glm::vec3& p_Values) const;
		void UploadUniformFloat4(const std::string& p_Name, const glm::vec4& p_Values) const;

		void UploadUniformMat3(const std::string& p_Name, const glm::mat3& p_Matrix) const;
		void UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix) const;
	private:
		uint32_t m_RendererID;
	};
}// namespace Pixel#pragma once
