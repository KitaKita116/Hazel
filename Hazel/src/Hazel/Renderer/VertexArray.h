#pragma once

#include <memory>
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind()const = 0;
		//添加VB
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		//设置IB
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		//获取VB
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers()const = 0;
		//获取IB
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();

	};

}