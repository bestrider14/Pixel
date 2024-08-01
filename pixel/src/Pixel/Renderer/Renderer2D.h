#pragma once

#include "OrthographicCamera.h"

namespace Pixel
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& p_Camera);
		static void EndScene();

		// Primitive
		static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
		static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
	};
}// namespace Pixel