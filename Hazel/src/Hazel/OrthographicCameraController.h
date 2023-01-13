#pragma once

#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Core/Timestep.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera()const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		//屏幕宽高比
		float m_AspectRatio;
		//屏幕缩放比
		float m_ZoomLevel = 1.0f;
		//相机
		OrthographicCamera m_Camera;
		//是否允许旋转
		bool m_Rotation;
		//相机位置
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		//相机旋转度数
		float m_CameraRotation = 0.0f;
		//相机移动速度，旋转速度
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}