#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Pixel/Events/ApplicationEvent.h"
#include "Window.h"

namespace Pixel 
{
	class PIXEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& p_E);
	private:
		bool OnWindowClose(WindowCloseEvent& p_E);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be define in CLIENT
	Application* CreateApplication();

}// namespace Pixel

