#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void SandBox2D::OnAttach()
{
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Pixel::Timestep p_Timestep)
{
	//Update
	m_CameraController.OnUpdate(p_Timestep);

	//Renderer
	Pixel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Pixel::RenderCommand::Clear();

	Pixel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Pixel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Pixel::Renderer2D::EndScene();

	//std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Pixel::Event& p_Event)
{
	m_CameraController.OnEvent(p_Event);
}
