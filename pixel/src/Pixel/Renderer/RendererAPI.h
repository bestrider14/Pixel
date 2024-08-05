#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Pixel
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetViewPort(uint32_t p_X, uint32_t p_Y, uint32_t p_Widht, uint32_t p_height) = 0;
		virtual void SetClearColor(const glm::vec4& p_Color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& p_VertexArray, uint32_t p_IndexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}// namespace Pixel