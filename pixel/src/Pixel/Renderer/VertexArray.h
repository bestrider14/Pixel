#pragma once

#include "Pixel/Renderer/Buffer.h"

namespace Pixel
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffers() const = 0;

		static VertexArray* Create();
	};
}// namespace Pixel


