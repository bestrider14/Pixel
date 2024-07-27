#include "pxpch.h"
#include "Renderer.h"

namespace Pixel
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& p_Camera)
	{
		m_SceneData->ViewProjectionMatrix = p_Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray, const glm::mat4& p_Transform)
	{
		p_Shader->Bind();
		p_Shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		p_Shader->UploadUniformMat4("u_Transform", p_Transform);

		p_VertexArray->Bind();
		RenderCommand::DrawIndexed(p_VertexArray);
	}
}