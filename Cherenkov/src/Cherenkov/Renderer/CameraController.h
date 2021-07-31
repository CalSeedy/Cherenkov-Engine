#pragma once
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Core/TimeStep.h"
#include "Cherenkov/Events/ApplicationEvent.h"
#include "Cherenkov/Events/MouseEvent.h"

namespace Cherenkov {
	class CameraController {
	public:
		virtual void onUpdate(Timestep dt) = 0;
		virtual void onEvent(Event& ev) = 0;
	};
	
	class OrthographicCameraController : public CameraController {
		float m_AspectRatio;
		float m_Zoom = 1.0f;
		glm::vec3 m_CameraPos = {0.0f, 0.0f, 0.0f};
		float m_CameraRotation = 0.0f;
		float m_PanSpeed = 10.0f;
		float m_RotSpeed = 90.0f;
		OrthographicCamera m_Camera;

		bool onMouseScrolled(MouseScrollEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	public:
		OrthographicCameraController(float aspectRatio);
		void resize(float width, float height);
		void onUpdate(Timestep dt) override;
		void onEvent(Event& ev) override;
		inline float getZoom() { return m_Zoom; }
		inline void setZoom(float zoom) { m_Zoom = zoom; }
		inline const OrthographicCamera& getCamera() const { return m_Camera; }
		inline OrthographicCamera& getCamera() { return m_Camera; }
	};
}