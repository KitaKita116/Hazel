#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class OrthographicCamera
	{
	public:
		//正交相机初始化
		OrthographicCamera(float left, float right, float bottom, float top);
		//获取相机位置
		const glm::vec3& GetPosition() const { return m_Position; }
		//设置相机位置
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		//获取相机旋转
		float GetRotation() const { return m_Rotation; }
		//设置相机旋转
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		//获取相机投影矩阵
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		//获取相机视图矩阵
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		//重新计算视图矩阵
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}