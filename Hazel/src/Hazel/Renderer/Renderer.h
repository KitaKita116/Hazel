#pragma once

#include "RenderCommand.h"

namespace Hazel
{

	class Renderer
	{
	public:
		//场景开始
		static void BeginScene();
		//场景结束
		static void EndScene();
		//渲染数据提交
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

}