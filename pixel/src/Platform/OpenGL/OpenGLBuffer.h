#pragma once

#include "Pixel/Renderer/Buffer.h"

namespace Pixel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* p_Vertices, uint32_t p_Size);
		virtual ~OpenGLVertexBuffer();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual inline void SetLayout(const BufferLayout& p_Layout) override { m_Layout = p_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* p_Indices, uint32_t p_Count);
		virtual ~OpenGLIndexBuffer();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}


