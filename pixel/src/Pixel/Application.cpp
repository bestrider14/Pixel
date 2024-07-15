#include "pxpch.h"
#include "Application.h"

#include "Pixel/Log.h"

#include <Glad/glad.h>

namespace Pixel
{

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* p_Layer)
	{
		m_LayerStack.PushLayer(p_Layer);
		p_Layer->OnAttach();
	}

	void Application::PushOverlay(Layer* p_Overlay)
	{
		m_LayerStack.PushOverlay(p_Overlay);
		p_Overlay->OnAttach();
	}

	void Application::OnEvent(Event& p_E)
	{
		EventDispatcher dispatcher(p_E);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(p_E);
			if (p_E.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& p_E)
	{
		m_Running = false;
		return true;
	}
}//namespace Pixel
