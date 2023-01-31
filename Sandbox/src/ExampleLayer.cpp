#include "ExampleLayer.h"
#include <imgui/imgui.h>
#include <glm/glm/gtc/type_ptr.hpp>

ExamplerLayer::ExamplerLayer()
	: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
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

	uint32_t indices[6] = { 0, 1, 2 , 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
	indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	m_Texture = Hazel::Texture2D::Create("assets/textures/awesomeface.png");

	auto textureShader = m_ShaderLibrary.Get("Texture");
	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExamplerLayer::OnUpdate(Hazel::Timestep ts)
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

void ExamplerLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExamplerLayer::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);
}