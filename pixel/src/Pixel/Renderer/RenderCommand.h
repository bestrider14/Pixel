#pragma once

#include "RendererAPI.h"

namespace Pixel
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewPort(uint32_t p_X, uint32_t p_Y, uint32_t p_Widht, uint32_t p_height) { s_RendererAPI->SetViewPort(p_X, p_Y, p_Widht, p_height); }
		inline static void SetClearColor(const glm::vec4& p_Color) { s_RendererAPI->SetClearColor(p_Color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray>& p_VertexArray)
		{
			s_RendererAPI->DrawIndexed(p_VertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}// namespace Pixel