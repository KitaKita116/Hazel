#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_faceTexture = Hazel::Texture2D::Create("assets/textures/awesomeface.png");
	m_kitaTexture = Hazel::Texture2D::Create("assets/textures/kita.jpg");
}

void Sandbox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();


}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();

	//Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::Renderer2D::ResetStats();
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
	}

	{
		HZ_PROFILE_SCOPE("Renderer Draw");

		static float rotation = 0;
		rotation += ts * 30;

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		//Hazel::Renderer2D::DrawQuad({ 0, 0 }, { 1,1 }, { 1,0,0,1 });
		Hazel::Renderer2D::DrawQuad({ 0,1 }, { 1,1 }, m_kitaTexture);
		//Hazel::Renderer2D::DrawRotatedQuad({ 1,0 }, { 1,1 }, 45, { 0,1,0,1 });
		//Hazel::Renderer2D::DrawRotatedQuad({ 1, 1 }, { 1,1 }, 45, m_kitaTexture);

		//Hazel::Renderer2D::SetLineWidth(20.0f);
		//Hazel::Renderer2D::DrawLine(glm::vec3(0.0, 0, 0), glm::vec3(1.0, 0.0, 0.0), glm::vec4(1.0f, 0.0, 0.0, 1.0));
		Hazel::Renderer2D::DrawRect(glm::mat4(1.0f), glm::vec4(1.0f, 0.0, 0.0, 1.0f));

		Hazel::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Hazel::Renderer2D::GetStats();

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}