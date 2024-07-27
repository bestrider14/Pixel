#pragma once

#include "Pixel/Core.h"
#include "Pixel/Events/Event.h"
#include "Pixel/Core/Timestep.h"

namespace Pixel
{
	class Layer
	{
	public:
		Layer(const std::string& p_debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep p_Timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& p_Event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}// namespace Pixel