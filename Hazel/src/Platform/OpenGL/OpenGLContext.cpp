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
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR)); //返回负责当前OpenGL实现厂商的名字
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));//返回一个渲染器标识符，通常是个硬件平台
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));//返回OpenGL版本号

#ifdef HZ_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HZ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif
	}

	void Hazel::OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}