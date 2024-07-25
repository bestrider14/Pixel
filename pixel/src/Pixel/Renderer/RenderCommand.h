#pragma once

#include "RendererAPI.h"

namespace Pixel
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& p_Color) { s_RendererAPI->SetClearColor(p_Color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& p_VertexArray)
		{
			s_RendererAPI->DrawIndexed(p_VertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}// namespace Pixel