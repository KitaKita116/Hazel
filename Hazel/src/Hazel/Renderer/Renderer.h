#pragma once

#include "Hazel/Renderer/RenderCommand.h"

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);
		//场景开始
		static void BeginScene(OrthographicCamera& camera);
		//场景结束
		static void EndScene();
		//渲染数据提交
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		//场景数据
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}