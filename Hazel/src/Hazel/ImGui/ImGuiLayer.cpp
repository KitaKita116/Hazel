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
		//参考文件example_sdl_opengl3的main.cpp编写
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();

		//创建imgui context
		ImGui::CreateContext();

		//io相关设置 
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // 允许键盘输入
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // 允许停靠
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 允许多视口
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		//设置主题颜色
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		//设置窗口style和透明度
		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f; //WindowRounding代表窗口角落的值, 设置为0.0代表是矩形窗口
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;//窗口背景透明度
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		//glfw相关初始化
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		//OpenGL相关初始化
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		//释放相关资源
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		// 这个函数应该只会执行一次具体的内容, 会在里面创建OpenGL的ShaderProgram
		ImGui_ImplOpenGL3_NewFrame();

		// 从glfw库里获取 时间、鼠标位置、窗口和Viewport大小等参数, 赋值给ImGui::IO
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