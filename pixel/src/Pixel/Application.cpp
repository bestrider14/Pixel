#include "Application.h"

#include "Pixel/Events/ApplicationEvent.h"
#include "Pixel/Log.h"

#include <iostream>

namespace Pixel
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		PX_TRACE(e);

		while (true);

	}
}//namespace Pixel
