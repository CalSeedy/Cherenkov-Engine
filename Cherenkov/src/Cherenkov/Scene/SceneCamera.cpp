#include "ckpch.h"
#include "SceneCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Cherenkov {

	SceneCamera::SceneCamera() {
		recalculate();
	}

	void SceneCamera::recalculate() {
		if (m_Type == ProjectionType::Orthographic) {
			m_Projection = glm::ortho(
				(m_AspectRatio * m_OrthographicSize) * -0.5f,
				(m_AspectRatio * m_OrthographicSize) * 0.5f,
				(m_OrthographicSize) * -0.5f,
				(m_OrthographicSize) * 0.5f,
				m_OrthographicNear, m_OrthographicFar
			);
		}
		else if (m_Type == ProjectionType::Perspective) {
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	}
	
	void SceneCamera::setProperties(float_t aspect, float_t orthoSize, float_t orthoNear, float_t orthoFar, float_t perspFOV, float_t perspNear, float_t perspFar) {
		m_AspectRatio = aspect;

		m_OrthographicSize = orthoSize;
		m_OrthographicNear = orthoNear;
		m_OrthographicFar = orthoFar;

		m_PerspectiveFOV = perspFOV;
		m_PerspectiveNear = perspNear;
		m_PerspectiveFar = perspFar;
		recalculate();
	}

	void SceneCamera::setPerspective(float_t fov, float_t near, float_t far) {

		m_PerspectiveFOV = glm::radians(fov);
		m_PerspectiveNear = near;
		m_PerspectiveFar = far;
		m_Type = ProjectionType::Perspective;

		recalculate();
	}

	void SceneCamera::setOrthographic(float_t size, float_t near, float_t far) {
		m_OrthographicSize = size;
		m_OrthographicNear = near;
		m_OrthographicFar = far;

		m_Type = ProjectionType::Orthographic;

		recalculate();
	}

	void SceneCamera::setViewport(uint32_t width, uint32_t height) {
		m_AspectRatio = (float)width / (float)height;
		recalculate();
	}

	void SceneCamera::setType(const ProjectionType type) {
		m_Type = type;
	}

}
