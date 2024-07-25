#pragma once

#include "Core.h"
#include "Window.h"
#include "Pixel/LayerStack.h"
#include "Pixel/Events/Event.h"
#include "Pixel/Events/ApplicationEvent.h"

#include "Pixel/ImGui/ImGuiLayer.h"

#include "Pixel/Renderer/Shader.h"
#include "Pixel/Renderer/Buffer.h"
#include "Pixel/Renderer/VertexArray.h"

#include "Pixel/Renderer/OrthographicCamera.h"

namespace Pixel 
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& p_E);

		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);

		inline Window& GetWindow() { return *m_Window; }

		static inline Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& p_E);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_Shader2;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;

		static Application* s_Instance;
	};

	// To be define in CLIENT
	Application* CreateApplication();

}// namespace Pixel

