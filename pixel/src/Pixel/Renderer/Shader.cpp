#include "pxpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Pixel
{
	Ref<Shader> Shader::Create(const std::string& p_Filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(p_Filepath);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& p_VertexSrc, const std::string& p_FragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(p_VertexSrc, p_FragmentSrc);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}// namespace Pixel