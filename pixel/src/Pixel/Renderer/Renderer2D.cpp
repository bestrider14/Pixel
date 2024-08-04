#include "pxpch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Pixel
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		PX_PROFILE_FUNCTION();
		
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float SqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(SqVertices, sizeof(SqVertices)));
		BufferLayout layout2 = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(layout2);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t SqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(SqIndices, sizeof(SqIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		PX_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& p_Camera)
	{
		PX_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		PX_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		PX_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", p_Color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), {p_Size.x, p_Size.y, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Texture, p_TilingFactor, p_TintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		PX_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", p_TintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", p_TilingFactor);
		p_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		PX_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", p_Color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), p_Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Texture, p_TilingFactor, p_TintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		PX_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", p_TintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", p_TilingFactor);
		p_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), p_Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}// namespace Pixel