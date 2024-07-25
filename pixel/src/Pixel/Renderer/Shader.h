#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Pixel
{
	class Shader
	{
	public:
		Shader(const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix);
	private:
		uint32_t m_RendererID;
	};
}// namespace Pixel