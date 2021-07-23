#pragma once
#include <Cherenkov.h>

class ExampleLayer : public Cherenkov::Layer
{
	Cherenkov::OrthographicCameraController		m_CameraController;

	float										m_ObjAngle{ 0.0f };
	glm::vec4									m_ObjColour{ 0.906f, 0.227f, 0.137f, 1.0f };
	float										m_ObjScale{ 1.0f };
	glm::vec3									m_ObjTranslate{ 0.0f };

	const float									m_PanSpeed = 5.0f;
	const float									m_RotSpeed = 70.0f;

	Cherenkov::Ref<Cherenkov::Shader>			m_Shader;
	Cherenkov::Ref<Cherenkov::ShaderLibrary>	m_ShaderLibrary;
	Cherenkov::Ref<Cherenkov::Texture2D>		m_Texture;
	Cherenkov::Ref<Cherenkov::Texture2D>		m_Texture2;
	Cherenkov::Ref<Cherenkov::Shader>			m_TextureShader;
	Cherenkov::Ref<Cherenkov::VertexArray>		m_VertexArray;

public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(Cherenkov::Timestep dt) override;
	virtual void onImGuiDraw() override;
	void onEvent(Cherenkov::Event& event) override;
};