#pragma once
//图形上下文基类
namespace Hazel
{
	class GraphicsContex
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}