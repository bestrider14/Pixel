#include "pxpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Pixel
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& p_Camera)
	{
		m_SceneData->ViewProjectionMatrix = p_Camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& p_Shader, const Ref<VertexArray>& p_VertexArray, const glm::mat4& p_Transform)
	{
		p_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(p_Shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(p_Shader)->UploadUniformMat4("u_Transform", p_Transform);

		p_VertexArray->Bind();
		RenderCommand::DrawIndexed(p_VertexArray);
	}
}