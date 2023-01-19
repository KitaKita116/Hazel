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
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		//初始化
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}