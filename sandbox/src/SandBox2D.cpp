#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SandBox2D::SandBox2D()
	: Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void SandBox2D::OnAttach()
{
	PX_PROFILE_FUNCTION();

	m_CheckerBoardTexture = Pixel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{
	PX_PROFILE_FUNCTION();
}

void SandBox2D::OnUpdate(Pixel::Timestep p_Timestep)
{
	PX_PROFILE_FUNCTION();

	//Update
	m_CameraController.OnUpdate(p_Timestep);

	//Renderer
	{
		PX_PROFILE_SCOPE("RendererPrep::OnUpdate");
		Pixel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pixel::RenderCommand::Clear();
	}

	{
		PX_PROFILE_SCOPE("RendererDraw::OnUpdate");
		Pixel::Renderer2D::BeginScene(m_CameraController.GetCamera()); 
		Pixel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Pixel::Renderer2D::DrawQuad({ 0.5f, -0.6f }, { 0.9f, 1.0f }, { 0.2f, 0.8f, 0.45f, 1.0f });
		//Pixel::Renderer2D::DrawRotatedQuad({ 0.5f, -0.6f }, { 0.9f, 1.0f }, glm::radians(45.0f), { 0.2f, 0.8f, 0.45f, 1.0f });
		//Pixel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture, 10.0f);
		Pixel::Renderer2D::EndScene();
	}
}

void SandBox2D::OnImGuiRender()
{
	PX_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Pixel::Event& p_Event)
{
	m_CameraController.OnEvent(p_Event);
}
