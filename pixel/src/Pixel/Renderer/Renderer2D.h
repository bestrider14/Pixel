#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

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
		static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));

		static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
		static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
		static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
	};
}// namespace Pixel