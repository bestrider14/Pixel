#pragma once

#include "Core.h"
#include "Window.h"
#include "Pixel/Core/LayerStack.h"
#include "Pixel/Events/Event.h"
#include "Pixel/Events/ApplicationEvent.h"
#include "Pixel/Core/Timestep.h"

#include "Pixel/ImGui/ImGuiLayer.h"

namespace Pixel 
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& p_Event);

		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& p_Event);
		bool OnWindowResize(WindowResizeEvent& p_Event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// To be define in CLIENT
	Application* CreateApplication();

}// namespace Pixel

