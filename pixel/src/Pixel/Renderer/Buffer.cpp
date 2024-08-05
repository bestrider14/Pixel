#include "pxpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Pixel
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(p_Size);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> Pixel::VertexBuffer::Create(float* p_Vertices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(p_Vertices, p_Size);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> Pixel::IndexBuffer::Create(uint32_t* p_Indices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(p_Indices, p_Size);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}// namespace Pixel


