#include "ckpch.h"
#include "EditorCamera.h"

#include "Cherenkov/Core/Input.h"

#include <glfw/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Cherenkov {

	EditorCamera::EditorCamera(float_t fov, float_t aspect, float_t near_, float_t far_) 
		: m_FOV{ fov }, m_AspectRatio{ aspect }, m_Near{ near_ }, m_Far{ far_ }, Camera(glm::perspective(glm::radians(fov), aspect, near_, far_)) { updateView(); }

	void EditorCamera::updateProjection() {
		m_AspectRatio = m_VpWidth / m_VpHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
	}

	void EditorCamera::updateView() {
		m_Position = calculatePosition();

		glm::quat orien = getOrientation();
		m_View = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orien));
	}

	bool EditorCamera::onMouseScroll(MouseScrollEvent& ev) {
		float_t delta = ev.getYOffset() * 0.1f;
		mouseZoom(delta);
		updateView();
		return false;
	}

	void EditorCamera::mousePan(const glm::vec2& delta) {
		auto [vx, vy] = panSpeed();
		m_FocalPoint += m_Distance * (vy * delta.y * getUpDirection() - vx * delta.x * getRightDirection());
	}

	void EditorCamera::mouseRotate(const glm::vec2& delta) {
		float_t sign = getUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += sign * delta.x * rotationSpeed();
		m_Pitch += delta.y * rotationSpeed();
	}

	void EditorCamera::mouseZoom(float_t delta) {
		m_Distance -= delta * zoomSpeed();
		if (m_Distance < 1.0f) {
			m_FocalPoint += getForwardDirection();
			m_Distance = 1.0f;
		}
	}

	glm::vec3 EditorCamera::calculatePosition() const {
		return m_FocalPoint - getForwardDirection() * m_Distance;
	}

	std::pair<float_t, float_t> EditorCamera::panSpeed() const {
		float_t x = std::min(m_VpWidth / 1000.0f, 2.4f);
		float_t outX = 0.0366f * (x * x) - 0.1778f * x + 3.021f;

		float_t y = std::min(m_VpHeight / 1000.0f, 2.4f);
		float_t outY = 0.0366f * (y * y) - 0.1778f * y + 3.021f;

		return { outX, outY };
	}

	float_t EditorCamera::rotationSpeed() const {
		return 0.8f;
	}

	float_t EditorCamera::zoomSpeed() const {
		float_t dist = std::max(m_Distance * 0.2f, 0.0f);
		float_t speed = std::min(dist * dist, 100.0f);
		return speed;
	}

	void EditorCamera::onEvent(Event& ev) {
		EventDispatcher disp(ev);
		disp.Dispatch<MouseScrollEvent>(CK_BIND_EVENT_FN(EditorCamera::onMouseScroll));
	}

	void EditorCamera::onUpdate(Timestep dt) {
		if (Input::isKeyPressed(Key::Left_Alt)) {
			const glm::vec2& mouse{ Input::getMouseX(), Input::getMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			if (Input::isMouseButtonPressed(Mouse::Button_Middle))
				mousePan(delta);
			else if (Input::isMouseButtonPressed(Mouse::Button_Left))
				mouseRotate(delta);
			else if (Input::isMouseButtonPressed(Mouse::Button_Right))
				mouseZoom(delta.y);
		}
		updateView();
	}

	glm::vec3 EditorCamera::getUpDirection() const {
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getRightDirection() const {
		return glm::rotate(getOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::getForwardDirection() const {
		return glm::rotate(getOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat EditorCamera::getOrientation() const {
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
}
