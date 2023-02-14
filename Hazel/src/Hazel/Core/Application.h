#pragma once

#include "Hazel/Core/Base.h"

#include "Hazel/Core/Window.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Timestep.h"

int main(int argc, char** argv);

namespace Hazel {

	class Application
	{
	public:
		Application(const std::string& name = "Hazel App");
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;//窗口
		ImGuiLayer* m_ImGuiLayer;//ui界面
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		//让main函数成为该类的友元函数
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}