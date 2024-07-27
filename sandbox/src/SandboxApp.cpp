#include <Pixel.h>

#include <glm/gtc/matrix_transform.hpp>

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

		std::shared_ptr<Pixel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Pixel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Pixel::BufferLayout layout = {
			{ Pixel::ShaderDataType::Float3, "a_Position" },
			{ Pixel::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Pixel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Pixel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Pixel::VertexArray::Create());

		float SqVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Pixel::VertexBuffer> squareVB;
		squareVB.reset(Pixel::VertexBuffer::Create(SqVertices, sizeof(SqVertices)));
		Pixel::BufferLayout layout2 = {
			{ Pixel::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(layout2);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t SqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Pixel::IndexBuffer> SquareIB;
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

		m_Shader.reset(new Pixel::Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
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

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2f, 0.3f, 0.9f, 1.0f);
			}
		)";

		m_Shader2.reset(new Pixel::Shader(vertexSrc2, fragmentSrc2));
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

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Pixel::Renderer::Submit(m_Shader2, m_SquareVA, transform);
			}
		}

		Pixel::Renderer::Submit(m_Shader, m_VertexArray);

		Pixel::Renderer::EndScene();
	}

	void OnEvent(Pixel::Event& p_Event) override
	{
	}

private:
	std::shared_ptr<Pixel::Shader> m_Shader;
	std::shared_ptr<Pixel::VertexArray> m_VertexArray;

	std::shared_ptr<Pixel::Shader> m_Shader2;
	std::shared_ptr<Pixel::VertexArray> m_SquareVA;

	Pixel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.00f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;
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