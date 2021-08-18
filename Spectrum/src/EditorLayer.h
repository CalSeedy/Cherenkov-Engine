#pragma once
#include <Cherenkov.h>
#include "Panels/SceneHierarchy.h"
#include "Panels/EntityProperties.h"

namespace Cherenkov {
	class EditorLayer : public Layer {
		Ref<Scene>							m_ActiveScene;

		// Assets for rendering
		Ref<Shader>							m_Shader;
		Ref<Texture2D>						m_Texture;
		Ref<VertexArray>					m_VertexArray;

		// Framebuffer/viewport
		EditorCamera						m_EditorCamera;
		Ref<Framebuffer>					m_Framebuffer;
		glm::vec2							m_VpBounds[2];
		bool								m_VpFocused = false;
		bool								m_VpHovered = false;
		glm::vec2							m_VpSize = {0, 0};

		// Profiling
		struct ProfileResult {
			const char* Name;
			float Time;
		};
		std::vector<ProfileResult>			m_Results;

		// Panels/Guizmos
		int									m_GuizmoOp = -1;
		std::string							m_SavePath{};
		SceneHierarchy						m_SceneHierarchy;
		EntityProperties					m_Properties;

		bool onKeyPressed(KeyPressedEvent& ev);
		bool onMouseButtonPressed(MouseButtonPressedEvent& ev);
		void openScene();
		void saveScene();
		void saveAs();
		void newScene();
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
