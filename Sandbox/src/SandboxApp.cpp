#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExamplerLayer : public Hazel::Layer
{
public:
	ExamplerLayer()
		: Layer("Example"), m_CameraController(1280.0f/720.0f,true)
	{
		m_VertexArray = Hazel::VertexArray::Create();

		float vertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));
		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float2, "a_TexCoords" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2 , 2, 3, 0};
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_Texture = Hazel::Texture2D::Create("assets/textures/awesomeface.png");

		auto textureShader = m_ShaderLibrary.Get("Texture");
		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Hazel::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

		auto textureShader = m_ShaderLibrary.Get("Texture");
		textureShader->Bind();

		m_Texture->Bind();
		Hazel::Renderer::Submit(textureShader, m_VertexArray);

		Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}
private:
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Ref<Hazel::Shader> m_Shader;//Shader÷∏’Î
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;//VAO÷∏’Î
	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Hazel::Application*  Hazel::CreateApplication()
{
	return new Sandbox();
}