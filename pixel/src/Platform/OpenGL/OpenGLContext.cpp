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

		PX_CORE_INFO("OpenGL Info:");
		PX_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PX_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PX_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}// namespace Pixel