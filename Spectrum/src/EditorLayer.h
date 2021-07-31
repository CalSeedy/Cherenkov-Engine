#pragma once
#include <Cherenkov.h>

#include "imgui/imgui.h"

namespace Cherenkov {
	class EditorLayer : public Layer {
		OrthographicCameraController		m_CameraController;

		Ref<Framebuffer>					m_Framebuffer;
		Ref<Shader>							m_Shader;
		Ref<Texture2D>						m_Texture;

		glm::vec4							m_ObjColour{ 0.906f, 0.227f, 0.137f, 1.0f };
		glm::vec3							m_SqPos{ 0.0f, 0.0f, 0.0f };
		Ref<VertexArray>					m_VertexArray;

		bool								m_VpFocused = false;
		bool								m_VpHovered = false;
		glm::vec2							m_VpSize;

		struct ProfileResult {
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult>			m_Results;
	public:
		EditorLayer();

		virtual ~EditorLayer() = default;

		virtual void onUpdate(Timestep dt) override;
		void onImGuiDraw() override;
		void onEvent(Event& ev) override;
		virtual void onAttach() override;
		virtual void onDetach() override;
	};
}