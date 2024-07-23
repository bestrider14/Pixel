#pragma once

#include <string>

namespace Pixel
{
	class Shader
	{
	public:
		Shader(const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;
	};
}// namespace Pixel