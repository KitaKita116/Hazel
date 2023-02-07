#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace Hazel
{
	class HazelEditor : public Application
	{
	public:
		HazelEditor()
			:Application("Hazel Editor")
		{
			PushLayer(new EditorLayer());
		}
		~HazelEditor()
		{

		}
	};

	Hazel::Application* Hazel::CreateApplication()
	{
		return new HazelEditor();
	}
}