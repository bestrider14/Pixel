#include "pxpch.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

#include "VertexArray.h"
#include "Shader.h"

namespace Pixel
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float SqVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(SqVertices, sizeof(SqVertices)));
		BufferLayout layout2 = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(layout2);
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t SqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(SqIndices, sizeof(SqIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(SquareIB);


		s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& p_Camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", p_Color);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}// namespace Pixel