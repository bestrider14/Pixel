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

	Ref<Shader> Shader::Create(const std::string& p_Name, const std::string& p_VertexSrc, const std::string& p_FragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: PX_CORE_ASSERT(false, "RendererAPI::None is curently not supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(p_Name ,p_VertexSrc, p_FragmentSrc);
		}

		PX_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& p_Name, const Ref<Shader>& p_Shader)
	{
		PX_CORE_ASSERT(!Exists(p_Name), "Shader already exist!");
		m_Shaders[p_Name] = p_Shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& p_Shader)
	{
		auto& name = p_Shader->GetName();
		Add(name, p_Shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& p_Name, const std::string& p_Filepath)
	{
		auto shader = Shader::Create(p_Filepath);
		Add(p_Name, shader);
		return Ref<Shader>();
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& p_Filepath)
	{
		auto shader = Shader::Create(p_Filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& p_Name)
	{
		PX_CORE_ASSERT(Exists(p_Name), "Shader not found!");
		return m_Shaders[p_Name];
	}

	bool ShaderLibrary::Exists(const std::string& p_Name) const
	{
		return m_Shaders.find(p_Name) != m_Shaders.end();
	}

}// namespace Pixel