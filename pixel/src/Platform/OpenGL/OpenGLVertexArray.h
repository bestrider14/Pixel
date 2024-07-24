#pragma once

#include "Pixel/Renderer/VertexArray.h"

namespace Pixel
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_VertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer) override;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
		virtual inline const std::shared_ptr<IndexBuffer>& getIndexBuffers() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererId;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}// namespace Pixel


