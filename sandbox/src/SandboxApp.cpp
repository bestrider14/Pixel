#include <Pixel.h>

class EmampleLayer : public Pixel::Layer
{
public:
	EmampleLayer()
		: Layer("Example") 
	{}

	void OnUpdate() override
	{
		if (Pixel::Input::IsKeyPressed(PX_KEY_UP))
			PX_TRACE("Key up is pressed!");
	}

	void OnEvent(Pixel::Event& p_Event) override
	{
		//PX_TRACE("{0}", p_Event);
	}
};

class Sandbox : public Pixel::Application
{
public:
	Sandbox()
	{
		PushLayer(new EmampleLayer());
	}

	~Sandbox()
	{

	}
};

Pixel::Application* Pixel::CreateApplication()
{
	return new Sandbox();
}