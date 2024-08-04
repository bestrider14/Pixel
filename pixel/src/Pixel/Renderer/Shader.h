#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Pixel
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& p_Name, int p_Value) = 0;
		virtual void SetFloat(const std::string& p_Name, float p_Value) = 0;
		virtual void SetFloat3(const std::string& p_Name, const glm::vec3& p_Value) = 0;
		virtual void SetFloat4(const std::string& p_Name, const glm::vec4& p_Value) = 0;
		virtual void SetMat4(const std::string& p_Name, const glm::mat4& p_Value) = 0;

		virtual const std::string& GetName() const = 0;
	
		static Ref<Shader> Create(const std::string& p_Filepath);
		static Ref<Shader> Create(const std::string& p_Name, const std::string& p_VertexSrc, const std::string& p_FragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& p_nNme, const Ref<Shader>& p_Shader);
		void Add(const Ref<Shader>& p_Shader);
		Ref<Shader> Load(const std::string& p_Name, const std::string& p_Filepath);
		Ref<Shader> Load(const std::string& p_Filepath);

		Ref<Shader> Get(const std::string& p_Name);

		bool Exists(const std::string& p_Name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}// namespace Pixel