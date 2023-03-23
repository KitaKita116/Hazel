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
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		//打开场景
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		//保存场景
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();
		//复制实体
		void OnDuplicateEntity();

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
		Ref<Framebuffer> m_EditorFramebuffer;
		Ref<Framebuffer> m_MainCameraFramebuffer;

		Ref<Scene> m_ActiveScene, m_EditorScene;
		std::filesystem::path m_EditorScenePath;

		Entity m_SquareEntity;
		Entity m_otherEntity;

		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportBounds[2];

		void OnOverlayRender();

		bool m_ShowPhysicsColliders = false;

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState m_SceneState = SceneState::Edit;

		Ref<Texture2D> m_IconPlay, m_IconStop, m_IconPause;

		Entity m_HoverEntity;
	};

}