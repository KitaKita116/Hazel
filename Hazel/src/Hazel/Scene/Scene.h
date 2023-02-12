#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"

namespace Hazel
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		//当视口大小变化时
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		//包含所有entity的容器
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}