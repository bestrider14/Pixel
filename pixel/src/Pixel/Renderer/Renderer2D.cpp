#include "pxpch.h"
#include "Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"

namespace Pixel
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};
	
	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		PX_PROFILE_FUNCTION();
		
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		PX_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& p_Camera)
	{
		PX_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		PX_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		PX_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = p_Position;
		s_Data.QuadVertexBufferPtr->Color = p_Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { p_Position.x + p_Size.x, p_Position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = p_Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { p_Position.x + p_Size.x, p_Position.y + p_Size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = p_Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { p_Position.x, p_Position.y + p_Size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = p_Color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		/*s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), {p_Size.x, p_Size.y, 1.0f});
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Texture, p_TilingFactor, p_TintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		PX_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", p_TintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", p_TilingFactor);
		p_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color)
	{
		PX_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", p_Color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), p_Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		DrawRotatedQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Rotation, p_Texture, p_TilingFactor, p_TintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor, const glm::vec4& p_TintColor)
	{
		PX_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", p_TintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", p_TilingFactor);
		p_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position)
			* glm::rotate(glm::mat4(1.0f), p_Rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
}// namespace Pixel