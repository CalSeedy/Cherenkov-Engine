#pragma once
#include <Cherenkov.h>
#include "Panels/SceneHierarchy.h"
#include "Panels/EntityProperties.h"

namespace Cherenkov {
	class EditorLayer : public Layer {
		Ref<Scene>							m_ActiveScene;
		Entity								m_CameraFirst;
		Entity								m_CameraOther;
		OrthographicCameraController		m_CameraController;

		Ref<Framebuffer>					m_Framebuffer;
		Ref<Shader>							m_Shader;
		Ref<Texture2D>						m_Texture;

		glm::vec4							m_ObjColour{ 0.906f, 0.227f, 0.137f, 1.0f };
		Entity								m_Square;
		glm::vec3							m_SqPos{ 0.0f, 0.0f, 0.0f };
		Ref<VertexArray>					m_VertexArray;

		bool								m_VpFocused = false;
		bool								m_VpHovered = false;
		glm::vec2							m_VpSize = {0, 0};

		struct ProfileResult {
			const char* Name;
			float Time;
		};

		SceneHierarchy						m_SceneHierarchy;
		EntityProperties					m_Properties;
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
