#include "pxpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "Glad/glad.h"

namespace Pixel
{
	OpenGLContext::OpenGLContext(GLFWwindow* p_WindowHandle)
		:m_WindowHandle(p_WindowHandle)
	{
		PX_CORE_ASSERT(p_WindowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PX_CORE_ASSERT(status, "Could not initialize Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}// namespace Pixel