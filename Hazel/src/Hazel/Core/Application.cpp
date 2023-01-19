#include "hzpch.h"
#include "Hazel/Core/Application.h"

#include "Hazel/Core/Log.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Hazel
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	Application::~Application()
	{
		Renderer::Shutdown();
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

		HZ_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)//如果事件已处理
				break;
		}
	}
	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}