#include "ckpch.h"
#include "Cherenkov/Renderer/CameraController.h"
#include "Cherenkov/Core/Input.h"
#include "Cherenkov/Core/KeyCodes.h"

float zoomFactor = 0.25f;
float zoomLimitLow = 0.1f;
float zoomLimitHigh = 10.0f;

namespace Cherenkov {
    bool OrthographicCameraController::onMouseScrolled(MouseScrollEvent& e) {
        m_Zoom -= e.getYOffset() * zoomFactor;
        m_Zoom = std::max(m_Zoom, zoomLimitLow);
        m_Zoom = std::min(m_Zoom, zoomLimitHigh);
        m_Camera.setProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent& e) {
        resize((float)e.getWidth(), (float)e.getHeight());
        
        return false;
    }

    OrthographicCameraController::OrthographicCameraController(float aspectRatio) : m_AspectRatio{ aspectRatio }, m_Camera { -m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom } {

    }

	void OrthographicCameraController::resize(float width, float height) {
        if (height != 0.0f) m_AspectRatio = width / height;
        m_Camera.setProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
	}

	void OrthographicCameraController::onUpdate(Timestep dt) {
        CK_PROFILE_FUNCTION();
        if (Input::isKeyPressed(Key::W)) {
            m_CameraPos.x += sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
            m_CameraPos.y += cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
        }
        else if (Input::isKeyPressed(Key::S)) {
            m_CameraPos.x -= sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
            m_CameraPos.y -= cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
        }
        if (Input::isKeyPressed(Key::A)) {
            m_CameraPos.x -= cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
            m_CameraPos.y -= sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
        }
        else if (Input::isKeyPressed(Key::D)) {
            m_CameraPos.x += cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
            m_CameraPos.y += sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;
        }
        if (m_Camera.getPosition() != m_CameraPos) m_Camera.setPosition(m_CameraPos);

        if (Input::isKeyPressed(Key::Q))
            m_CameraRotation += m_RotSpeed * dt;

        else if (Input::isKeyPressed(Key::E))
            m_CameraRotation -= m_RotSpeed * dt;

        if (m_Camera.getRotation() != m_CameraRotation) m_Camera.setRotation(m_CameraRotation);
        while (m_CameraRotation > 360.0f) m_CameraRotation -= 360.0f;
    }

    void OrthographicCameraController::onEvent(Event& ev) {
        CK_PROFILE_FUNCTION();
        EventDispatcher dis(ev);
        dis.Dispatch<MouseScrollEvent>(CK_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dis.Dispatch<WindowResizeEvent>(CK_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }
}
