#pragma once

#include <string>

namespace Pixel
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		static Shader* Create(const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
	};
}// namespace Pixel