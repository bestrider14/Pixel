#pragma once

#ifdef PX_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication();

int main(int argc, char** argv)
{
	printf("Pixel start up!");
	auto app = Pixel::CreateApplication();
	app->Run();
	delete app;
}

#endif