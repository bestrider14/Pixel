#include "pxpch.h"
#include "Application.h"

#include "Pixel/Events/ApplicationEvent.h"
#include "Pixel/Log.h"

#include <iostream>

namespace Pixel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}//namespace Pixel
