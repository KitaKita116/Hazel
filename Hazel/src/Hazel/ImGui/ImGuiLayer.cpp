#include "hzpch.h"
#include "Hazel/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Hazel/Core/Application.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		//�ο��ļ�example_sdl_opengl3��main.cpp��д
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();

		//����imgui context
		ImGui::CreateContext();

		//io������� 
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // �����������
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // ����ͣ��
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // ������ӿ�
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		//����������ɫ
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		//���ô���style��͸����
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f; //WindowRounding�����ڽ����ֵ, ����Ϊ0.0�����Ǿ��δ���
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;//���ڱ���͸����
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//glfw��س�ʼ��
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		//OpenGL��س�ʼ��
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		//�ͷ������Դ
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		// �������Ӧ��ֻ��ִ��һ�ξ��������, �������洴��OpenGL��ShaderProgram
		ImGui_ImplOpenGL3_NewFrame();

		// ��glfw�����ȡ ʱ�䡢���λ�á����ں�Viewport��С�Ȳ���, ��ֵ��ImGui::IO
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

}