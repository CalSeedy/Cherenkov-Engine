#pragma once
#include <Cherenkov.h>

#include "imgui/imgui.h"

class Sandbox2D : public Cherenkov::Layer {
	Cherenkov::OrthographicCameraController		m_CameraController;

	Cherenkov::Ref<Cherenkov::Framebuffer>		m_Framebuffer;
	Cherenkov::Ref<Cherenkov::Shader>			m_Shader;
	Cherenkov::Ref<Cherenkov::Texture2D>		m_Texture;

	glm::vec4									m_ObjColour{ 0.906f, 0.227f, 0.137f, 1.0f };
	glm::vec3									m_SqPos{ 0.0f, 0.0f, 0.0f };
	Cherenkov::Ref<Cherenkov::VertexArray>		m_VertexArray;

	struct ProfileResult {
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult>					m_Results;
public:
	Sandbox2D();

	virtual ~Sandbox2D() = default;

	virtual void onUpdate(Cherenkov::Timestep dt) override;
	void onImGuiDraw() override;
	void onEvent(Cherenkov::Event& ev) override;
	virtual void onAttach() override;
	virtual void onDetach() override;
};