#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		//���������ɫ
		virtual void SetClearColor(const glm::vec4& color) override;
		//�������
		virtual void Clear() override;
		//��ʾVAO������
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

		virtual void Init() override;
	};
}