#include "pxpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Pixel
{
	Ref<Texture2D> Texture2D::Create(const std::string& p_Path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(p_Path);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}// namespace Pixel