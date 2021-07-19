#include "ckpch.h"
#include "CameraController.h"
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
        m_AspectRatio = (float)e.getWidth() / (float)e.getHeight();
        m_Camera.setProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
        return false;
    }

    OrthographicCameraController::OrthographicCameraController(float aspectRatio) : m_AspectRatio{ aspectRatio }, m_Camera { -m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom } {

    }

    void OrthographicCameraController::onUpdate(Timestep dt) {
        if (Input::isKeyPressed(CK_KEY_W))
            m_CameraPos.y += sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;

        else if (Input::isKeyPressed(CK_KEY_S))
            m_CameraPos.y -= sin(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;

        if (Input::isKeyPressed(CK_KEY_A))
            m_CameraPos.x -= cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;

        else if (Input::isKeyPressed(CK_KEY_D))
            m_CameraPos.x += cos(glm::radians(m_CameraRotation)) * m_PanSpeed * dt;

        if (m_Camera.getPosition() != m_CameraPos) m_Camera.setPosition(m_CameraPos);

        if (Input::isKeyPressed(CK_KEY_Q))
            m_CameraRotation += m_RotSpeed * dt;

        else if (Input::isKeyPressed(CK_KEY_E))
            m_CameraRotation -= m_RotSpeed * dt;

        if (m_Camera.getRotation() != m_CameraRotation) m_Camera.setRotation(m_CameraRotation);
        while (m_CameraRotation > 180.0f) m_CameraRotation -= 180.0f
    }

    void OrthographicCameraController::onEvent(Event& ev) {
        EventDispatcher dis(ev);
        dis.Dispatch<MouseScrollEvent>(CK_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dis.Dispatch<WindowResizeEvent>(CK_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }
}