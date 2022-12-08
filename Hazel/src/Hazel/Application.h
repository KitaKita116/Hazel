#pragma once


#include "Window.h"
#include "Events/Event.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application() = default;
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;//窗口
		ImGuiLayer* m_ImGuiLayer;//ui界面
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;//Shader指针
		std::unique_ptr<VertexBuffer> m_VertexBuffer;//顶点缓冲指针
		std::unique_ptr<IndexBuffer> m_IndexBuffer;//顶点索引指针

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

