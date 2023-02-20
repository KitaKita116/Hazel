#pragma once

#include <Hazel.h>
#include "SceneHierarchyPanel.h"
#include "ContentBrowserPanel.h"

#include "Hazel/Renderer/EditorCamera.h"

namespace Hazel
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();

		void OnScenePlay();
		void OnSceneStop();

		// UI Panels
		void UI_Toolbar();
	private:
		OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_faceTexture;
		Ref<Texture2D> m_kitaTexture;

		int m_GizmoType = -1;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Framebuffer> m_EditorFramebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_otherEntity;

		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;

		Ref<Texture2D> m_IconPlay, m_IconStop, m_IconPause;
	};

}