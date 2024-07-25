#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Pixel/Renderer/Shader.h"

namespace Pixel
{
	 class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& p_Camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}


