#include "hzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	Hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void Hazel::OpenGLContext::Init()
	{
		HZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL info:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR)); //���ظ���ǰOpenGLʵ�ֳ��̵�����
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));//����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));//����OpenGL�汾��

		HZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void Hazel::OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}