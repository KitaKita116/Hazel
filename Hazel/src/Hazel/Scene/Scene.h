#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/Renderer/EditorCamera.h"
#include "entt.hpp"
#include "Hazel/Core/UUID.h"

class b2World;

namespace Hazel
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntityWithUUID(UUID uuid, const std::string& name);
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		//当视口大小变化时
		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimatyCamera();

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		//包含所有entity的容器
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}