#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Pixel/Renderer/Shader.h"

namespace Pixel
{
	 class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t p_Width, uint32_t p_Height);

		static void BeginScene(OrthographicCamera& p_Camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& p_Shader, const Ref<VertexArray>& p_VertexArray, const glm::mat4& p_Transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}


