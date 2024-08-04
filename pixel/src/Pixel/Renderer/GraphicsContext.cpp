#include "pxpch.h"
#include "Pixel/Renderer/GraphicsContext.h"

#include "Pixel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Pixel 
{

	Scope<GraphicsContext> GraphicsContext::Create(void* p_Window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(p_Window));
		}

		PX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}// namespace Pixel