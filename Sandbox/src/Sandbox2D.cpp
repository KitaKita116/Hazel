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
		//Hazel::Renderer2D::DrawQuad({ 1, 0 }, { 1,1 }, { 1,0,0,1 });
		//Hazel::Renderer2D::DrawQuad({ 0, 1 }, { 1,1 }, { 0,1,0,1 });
		//Hazel::Renderer2D::DrawQuad({ 1, 1 }, { 1,1 }, { 0,0,1,1 });
		//Hazel::Renderer2D::DrawRotatedQuad({ 0, 0 }, { 1,1 }, 0, m_kitaTexture);
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				//float cr = (x + 5)/10.0f;
				//float cy = (y + 5)/10.0f;
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Hazel::Renderer2D::DrawQuad({ x,y,1 }, { 0.30f,0.30f }, color);
			}
		}
		//for(float y = -5.0f; y < 5.0f; y += 0.5f)
		//{
		//	for (float x = -5.0f; x < 5.0f; x += 0.5f)
		//	{
		//		glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
		//		Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		//	}
		//}
		Hazel::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D status:");
	ImGui::Text("DrawCall:%d", stats.DrawCall);
	ImGui::Text("Quad Count:%d", stats.QuadCount);
	ImGui::Text("Vertex Count:%d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count:%d", stats.GetTotalindicesCount());
	//ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}