#pragma once
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Core/TimeStep.h"

#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Events/MouseEvent.h"


namespace Cherenkov {

	class EditorCamera : public Camera {
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_Near = 0.1f, m_Far = 1000.0f;

		glm::mat4 m_View;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		float m_VpWidth = 1280, m_VpHeight = 720;

		void updateProjection();
		void updateView();

		bool onMouseScroll(MouseScrollEvent& ev);

		void mousePan(const glm::vec2& delta);
		void mouseRotate(const glm::vec2& delta);
		void mouseZoom(float_t delta);

		glm::vec3 calculatePosition() const;

		std::pair<float_t, float_t> panSpeed() const;
		float_t rotationSpeed() const;
		float_t zoomSpeed() const;
	public:
		EditorCamera() = default;
		EditorCamera(float_t fov, float_t aspect, float_t near_, float_t far_);

		void onEvent(Event& ev);
		void onUpdate(Timestep dt);
		void setViewport(float_t width, float_t height) { m_VpWidth = width; m_VpHeight = height; updateProjection(); }


		void getDistance(float_t distance) { m_Distance = distance; }
		float_t setDistance() { return m_Distance; }

		const glm::mat4& getView() const { return m_View; }
		glm::mat4 getViewProjection() const { return m_Projection * m_View; }

		glm::vec3 getUpDirection() const;
		glm::vec3 getRightDirection() const;
		glm::vec3 getForwardDirection() const;

		const glm::vec3& getPosition() const { return m_Position; }
		glm::quat getOrientation() const;

		float_t getPitch() const { return m_Pitch; }
		float_t getYaw() const { return m_Yaw; }
	};

}
