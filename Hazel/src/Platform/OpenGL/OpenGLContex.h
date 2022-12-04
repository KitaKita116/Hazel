#pragma once

#include "Hazel/Renderer/GraphicsContex.h"

struct GLFWwindow;

namespace Hazel
{
	class OpenGLContex :public GraphicsContex
	{
	public:
		OpenGLContex(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}