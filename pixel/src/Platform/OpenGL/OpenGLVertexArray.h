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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer) override;

		virtual inline const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
		virtual inline const Ref<IndexBuffer>& getIndexBuffers() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererId;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}// namespace Pixel


