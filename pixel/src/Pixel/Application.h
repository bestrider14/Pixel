#pragma once

#include "Core.h"

namespace Pixel 
{
	class PIXEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be define in CLIENT
	Application* CreateApplication();

}// namespace Pixel

