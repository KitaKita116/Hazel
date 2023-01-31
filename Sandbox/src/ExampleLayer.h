#include "Hazel.h"

class ExamplerLayer : public Hazel::Layer
{
public:
	ExamplerLayer();
	~ExamplerLayer() = default;

	void OnUpdate(Hazel::Timestep ts) override;

	void OnImGuiRender() override;

	void OnEvent(Hazel::Event& event) override;
private:
	Hazel::ShaderLibrary m_ShaderLibrary;
	Hazel::Ref<Hazel::Shader> m_Shader;//Shader÷∏’Î
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;//VAO÷∏’Î
	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};