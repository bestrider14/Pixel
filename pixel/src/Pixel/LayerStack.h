#pragma once

#include "Pixel/Core.h"
#include "Layer.h"

namespace Pixel
{
	class  LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);
		void PopLayer(Layer* p_Layer);
		void PopOverlay(Layer* p_Overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}// namespace Pixel


