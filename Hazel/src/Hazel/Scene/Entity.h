#pragma once

#include "Scene.h"
#include "entt.hpp"
#include "Hazel/Core/UUID.h"
#include "Components.h"

namespace Hazel
{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		//������
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			//����������������û�е���viewportsize������
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}
		//��ӻ��߸������
		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			//����������������û�е���viewportsize������
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}
		//��ȡ���
		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		//�Ƿ���ĳ�����
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}
		//�Ƴ����
		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		//�ṩһ�������͵�bool����ʽת��
		operator bool() const { return m_EntityHandle != entt::null; }
		entt::entity getEntityID() { return m_EntityHandle; }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}


	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};

}