#include <Pixel.h>

class Sandbox : public Pixel::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Pixel::Application* Pixel::CreateApplication()
{
	return new Sandbox();
}