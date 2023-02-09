#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"

namespace Hazel
{

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		//包含所有entity的容器
		entt::registry m_Registry;
	};

}