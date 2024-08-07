#include "pxpch.h"
#include "WindowsWindow.h"

#include "Pixel/Events/ApplicationEvent.h"
#include "Pixel/Events/KeyEvent.h"
#include "Pixel/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Pixel
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int p_Error, const char* p_Description)
	{
		PX_CORE_ERROR("GLFW Error ({0}): {1}", p_Error, p_Description);
	}

	Scope<Window> Window::Create(const WindowProps& p_props)
	{
		return CreateScope<WindowsWindow>(p_props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& p_props)
	{
		PX_PROFILE_FUNCTION();

		Init(p_props);
	}

	WindowsWindow::~WindowsWindow()
	{
		PX_PROFILE_FUNCTION();
		
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& p_props)
	{
		PX_PROFILE_FUNCTION();
		
		m_Data.Title = p_props.Title;
		m_Data.Width = p_props.Width;
		m_Data.Height = p_props.Height;
		
		PX_CORE_INFO("Creating window {0} ({1}, {2})", p_props.Title, p_props.Width, p_props.Height);

		if (s_GLFWWindowCount == 0)
		{
			PX_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			PX_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			PX_PROFILE_SCOPE("glfwCreateWindow");
			m_Window = glfwCreateWindow((int)p_props.Width, (int)p_props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* p_Window, int p_Width, int p_Height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			data.Width = p_Width;
			data.Height = p_Height;

			WindowResizeEvent event(p_Width, p_Height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* p_Window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* p_Window, int p_Key, int p_Scancode, int p_Action, int p_Mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			switch (p_Action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(p_Key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(p_Key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(p_Key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* p_Window,unsigned int p_Keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			KeyTypedEvent event(p_Keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* p_Window, int p_Button, int p_Action, int p_Mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			switch (p_Action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(p_Button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(p_Button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* p_Window, double p_XOffset, double p_YOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			MouseScrolledEvent event((float)p_XOffset, (float)p_YOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* p_Window, double p_XPos, double p_YPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			MouseMovedEvent event((float)p_XPos, (float)p_YPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		PX_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		PX_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		PX_PROFILE_FUNCTION();
		
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