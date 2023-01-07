#pragma once

#include "Hazel/Core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{

	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		//层被推送
		virtual void OnAttach() {};
		//层被移除
		virtual void OnDetach() {};
		//层被更新
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}
