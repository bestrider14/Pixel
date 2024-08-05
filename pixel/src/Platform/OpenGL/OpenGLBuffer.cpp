#include "pxpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Pixel
{
	// VertexBuffer
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t p_Size)
	{
		PX_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* p_Vertices, uint32_t p_Size)
	{
		PX_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, p_Vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		PX_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		PX_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		PX_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* p_data, uint32_t p_Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, p_Size, p_data);
	}



	// IndexBuffer
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* p_Indices, uint32_t p_Count)
		: m_Count(p_Count)
	{
		PX_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_Count * sizeof(uint32_t), p_Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		PX_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		PX_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		PX_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}// namespace Pixel