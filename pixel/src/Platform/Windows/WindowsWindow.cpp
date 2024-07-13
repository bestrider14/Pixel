#include "pxpch.h"
#include "WindowsWindow.h"

namespace Pixel
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& p_props)
	{
		return new WindowsWindow(p_props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& p_props)
	{
		Init(p_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& p_props)
	{
		m_Data.Title = p_props.Title;
		m_Data.Width = p_props.Width;
		m_Data.Height = p_props.Height;

		PX_CORE_INFO("Creating window {0} ({1}, {2})", p_props.Title, p_props.Width, p_props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on systeme shutdown
			int success = glfwInit();
			PX_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)p_props.Width, (int)p_props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}// namespace Pixel