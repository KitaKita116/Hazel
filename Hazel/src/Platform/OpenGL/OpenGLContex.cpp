#include "hzpch.h"
#include "OpenGLContex.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	Hazel::OpenGLContex::OpenGLContex(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void Hazel::OpenGLContex::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL info:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR)); //返回负责当前OpenGL实现厂商的名字
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));//返回一个渲染器标识符，通常是个硬件平台
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));//返回OpenGL版本号
	}

	void Hazel::OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}