#pragma once

#ifdef PX_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication();

int main(int argc, char** argv)
{
	Pixel::Log::Init();

	PX_PROFILE_BEGIN_SESSION("Startup", "PixelProfile-Startup.json");
	auto app = Pixel::CreateApplication();
	PX_PROFILE_END_SESSION();

	PX_PROFILE_BEGIN_SESSION("Runtime", "PixelProfile-Runtime.json");
	app->Run();
	PX_PROFILE_END_SESSION();

	PX_PROFILE_BEGIN_SESSION("Shutdown", "PixelProfile-Shutdown.json");
	delete app;
	PX_PROFILE_END_SESSION();
}

#endif