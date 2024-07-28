#pragma once

#include "Pixel/Renderer/RendererAPI.h"

namespace Pixel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& p_Color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& p_VertexArray) override;
	};
}// namespace Pixel

