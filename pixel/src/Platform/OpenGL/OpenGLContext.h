#pragma once

#include "Pixel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Pixel
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* p_WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}// namespace Pixel
