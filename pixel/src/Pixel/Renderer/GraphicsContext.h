#pragma once

namespace Pixel
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* p_Window);
	};

}// namespace Pixel