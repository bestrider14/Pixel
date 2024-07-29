#include "pxpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Pixel
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType p_Type)
	{
		switch (p_Type)
		{
			case Pixel::ShaderDataType::Float:	return GL_FLOAT;
			case Pixel::ShaderDataType::Float2:	return GL_FLOAT;
			case Pixel::ShaderDataType::Float3:	return GL_FLOAT;
			case Pixel::ShaderDataType::Float4:	return GL_FLOAT;
			case Pixel::ShaderDataType::Mat3:	return GL_FLOAT;
			case Pixel::ShaderDataType::Mat4:	return GL_FLOAT;
			case Pixel::ShaderDataType::Int:	return GL_INT;
			case Pixel::ShaderDataType::Int2:	return GL_INT;
			case Pixel::ShaderDataType::Int3:	return GL_INT;
			case Pixel::ShaderDataType::Int4:	return GL_INT;
			case Pixel::ShaderDataType::Bool:	return GL_BOOL;
		}

		PX_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer)
	{
		PX_CORE_ASSERT(p_VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

		glBindVertexArray(m_RendererId);
		p_VertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = p_VertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(p_VertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer)
	{
		glBindVertexArray(m_RendererId);
		p_IndexBuffer->Bind();

		m_IndexBuffer = p_IndexBuffer;
	}
}// namespace Pixel
