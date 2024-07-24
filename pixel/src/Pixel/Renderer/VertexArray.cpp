#include "pxpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Pixel
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
			case RendererAPI::OpenGl: return new OpenGLVertexArray();
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}// namespace Pixel