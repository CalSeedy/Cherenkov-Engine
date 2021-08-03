#include "ckpch.h"
#include "SceneCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Cherenkov {

	SceneCamera::SceneCamera() {
		recalculate();
	}

	void SceneCamera::recalculate() {
		m_Projection = glm::ortho(
			(m_AspectRatio * m_OrthographicSize) * -0.5f,
			(m_AspectRatio * m_OrthographicSize) * 0.5f,
			(m_OrthographicSize) * -0.5f,
			(m_OrthographicSize) * 0.5f,
			m_OrthographicNear, m_OrthographicFar
		);
	}
	
	void SceneCamera::setOrthographic(float_t size, float_t near, float_t far) {
		m_OrthographicSize = size;
		m_OrthographicNear = near;
		m_OrthographicFar = far;

		recalculate();
	}

	void SceneCamera::setViewport(uint32_t width, uint32_t height) {
		float m_AspectRatio = (float)width / (float)height;
		recalculate();
	}

}