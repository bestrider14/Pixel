#pragma once

#include "Pixel/Layer.h"

#include "Pixel/Events/KeyEvent.h"
#include "Pixel/Events/MouseEvent.h"
#include "Pixel/Events/ApplicationEvent.h"

namespace Pixel
{
	class PIXEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& p_Event) override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& p_Event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& p_Event);
		bool OnMouseMovedEvent(MouseMovedEvent& p_Event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& p_Event);
		bool OnKeyPressedEvent(KeyPressedEvent& p_Event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& p_Event);
		bool OnKeyTypedEvent(KeyTypedEvent& p_Event);
		bool OnWindowResizeEvent(WindowResizeEvent& p_Event);
	private:
		float m_Time = 0.0f;
	};
}// namespace Pixel



