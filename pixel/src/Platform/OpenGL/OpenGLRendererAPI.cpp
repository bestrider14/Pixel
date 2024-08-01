#include "pxpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Pixel
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewPort(uint32_t p_X, uint32_t p_Y, uint32_t p_Widht, uint32_t p_height)
	{
		glViewport(p_X, p_Y, p_Widht, p_height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& p_Color)
	{
		glClearColor(p_Color.r, p_Color.g, p_Color.b, p_Color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& p_VertexArray)
	{
		glDrawElements(GL_TRIANGLES, p_VertexArray->getIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}// namespace Pixel