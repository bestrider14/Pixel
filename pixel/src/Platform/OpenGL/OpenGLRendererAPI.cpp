#include "pxpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Pixel
{
	void OpenGLRendererAPI::Init()
	{
		PX_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
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

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& p_VertexArray, uint32_t p_IndexCount)
	{
		uint32_t count = p_IndexCount ? p_VertexArray->getIndexBuffers()->GetCount() : p_IndexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}// namespace Pixel