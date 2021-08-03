#include "ckpch.h"
#include "Cherenkov/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cherenkov {
	void OrthographicCamera::recalculateMatrices() {
		CK_PROFILE_FUNCTION();
		glm::mat4 mat = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), {0.0f, 0.0f, 1.0f});
		m_View = glm::inverse(mat);
		m_ViewProjection = m_Projection * m_View;
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View{ 1.0f } {
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far) {
		CK_PROFILE_FUNCTION();
		m_Projection = glm::ortho(left, right, bottom, top, near, far);
		m_ViewProjection = m_Projection * m_View;
	}
}

