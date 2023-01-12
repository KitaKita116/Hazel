#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		//设置清楚颜色
		virtual void SetClearColor(const glm::vec4& color) override;
		//清楚缓冲
		virtual void Clear() override;
		//显示VAO的内容
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		virtual void Init() override;
	};
}