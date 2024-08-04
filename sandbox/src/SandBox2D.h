#pragma once

#include "Pixel.h"

class SandBox2D : public Pixel::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	virtual void OnAttach();
	virtual void OnDetach();

	void OnUpdate(Pixel::Timestep p_Timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Pixel::Event& p_Event) override;
private:
	Pixel::OrthographicCameraController m_CameraController;

	//Temp
	Pixel::Ref<Pixel::VertexArray> m_SquareVA;
	Pixel::Ref<Pixel::Shader> m_FlatColorShader;

	Pixel::Ref<Pixel::Texture2D> m_CheckerBoardTexture;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};