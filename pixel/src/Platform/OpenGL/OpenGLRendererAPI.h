#pragma once

#include "Pixel/Renderer/RendererAPI.h"

namespace Pixel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewPort(uint32_t p_X, uint32_t p_Y, uint32_t p_Widht, uint32_t p_height) override;

		virtual void SetClearColor(const glm::vec4& p_Color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& p_VertexArray, uint32_t p_IndexCount = 0) override;
	};
}// namespace Pixel


