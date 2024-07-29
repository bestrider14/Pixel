#include <Pixel.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Pixel::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Pixel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.6f, 0.0f, 0.9f, 1.0f
		};

		Pixel::Ref<Pixel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Pixel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Pixel::BufferLayout layout = {
			{ Pixel::ShaderDataType::Float3, "a_Position" },
			{ Pixel::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Pixel::Ref<Pixel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Pixel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Pixel::VertexArray::Create());

		float SqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Pixel::Ref<Pixel::VertexBuffer> squareVB;
		squareVB.reset(Pixel::VertexBuffer::Create(SqVertices, sizeof(SqVertices)));
		Pixel::BufferLayout layout2 = {
			{ Pixel::ShaderDataType::Float3, "a_Position" },
			{ Pixel::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t SqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Pixel::Ref<Pixel::IndexBuffer> SquareIB;
		SquareIB.reset(Pixel::IndexBuffer::Create(SqIndices, sizeof(SqIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Pixel::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Pixel::Shader::Create(flatColorVertexSrc, flatColorShaderFragmentSrc));

		m_TextureShader.reset(Pixel::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Pixel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Pixel::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Pixel::Timestep p_Timestep) override
	{

		if (Pixel::Input::IsKeyPressed(PX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * p_Timestep;

		if (Pixel::Input::IsKeyPressed(PX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * p_Timestep;
		
		Pixel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pixel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Pixel::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Pixel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Pixel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Pixel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_ChernoLogoTexture->Bind();
		Pixel::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Triangle
		// Pixel::Renderer::Submit(m_Shader, m_VertexArray);

		Pixel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Pixel::Event& p_Event) override
	{
	}

private:
	Pixel::Ref<Pixel::Shader> m_Shader;
	Pixel::Ref<Pixel::VertexArray> m_VertexArray;

	Pixel::Ref<Pixel::Shader> m_FlatColorShader, m_TextureShader;
	Pixel::Ref<Pixel::VertexArray> m_SquareVA;

	Pixel::Ref<Pixel::Texture2D> m_Texture, m_ChernoLogoTexture;

	Pixel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.00f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Pixel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Pixel::Application* Pixel::CreateApplication()
{
	return new Sandbox();
}