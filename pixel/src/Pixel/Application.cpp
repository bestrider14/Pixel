#include "pxpch.h"
#include "Application.h"

#include "Pixel/Log.h"

#include <iostream>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Pixel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& p_E)
	{
		EventDispatcher dispatcher(p_E);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
		PX_CORE_TRACE("{0}", p_E);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& p_E)
	{
		m_Running = false;
		return true;
	}
}//namespace Pixel
