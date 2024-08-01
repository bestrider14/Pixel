#pragma once

#ifdef PX_PLATFORM_WINDOWS

extern Pixel::Application* Pixel::CreateApplication();

int main(int argc, char** argv)
{
	Pixel::Log::Init();

	PX_CORE_ERROR("Init Core Log!");
	int a = 5;
	PX_WARN("Init Client Log! Var={0}", a);

	auto app = Pixel::CreateApplication();
	app->Run();
	delete app;
}

#endif