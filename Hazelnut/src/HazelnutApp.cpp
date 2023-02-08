#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace Hazel
{
	class Hazelnut : public Application
	{
	public:
		Hazelnut()
			:Application("Hazel Editor")
		{
			PushLayer(new EditorLayer());
		}
		~Hazelnut()
		{

		}
	};

	Hazel::Application* Hazel::CreateApplication()
	{
		return new Hazelnut();
	}
}