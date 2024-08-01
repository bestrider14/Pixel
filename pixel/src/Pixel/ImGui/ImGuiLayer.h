#pragma once

#include "Pixel/Core/Layer.h"

#include "Pixel/Events/KeyEvent.h"
#include "Pixel/Events/MouseEvent.h"
#include "Pixel/Events/ApplicationEvent.h"

namespace Pixel
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}// namespace Pixel



