#include "pxpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Pixel
{
	VertexBuffer* Pixel::VertexBuffer::Create(float* p_Vertices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::OpenGl: return new OpenGLVertexBuffer(p_Vertices, p_Size);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	IndexBuffer* Pixel::IndexBuffer::Create(uint32_t* p_Indices, uint32_t p_Count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::OpenGl: return new OpenGLIndexBuffer(p_Indices, p_Count);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}// namespace Pixel


