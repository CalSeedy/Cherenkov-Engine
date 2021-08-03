#pragma once
#include <glm/glm.hpp>

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif
namespace Cherenkov {

	class Camera {
	protected:
		glm::mat4 m_Projection;
	public:
		Camera() : m_Projection{ glm::mat4(1.0f) } {}
		Camera(const glm::mat4& projection) : m_Projection{ projection } {}
		virtual ~Camera() = default;

		const glm::mat4& getProjection() const { return m_Projection; }
	};

	class OrthographicCamera : Camera {
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		//glm::mat4 m_Projection;
		
		float m_Rotation = 0.0f;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		void recalculateMatrices();
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::mat4& getProjection() const { return m_Projection; }
		const glm::mat4& getViewProjection() const { return m_ViewProjection; }
		const glm::mat4& getView() const { return m_View; }

		const glm::vec3& getPosition() const {  return m_Position;  }
		const float& getRotation() const { return m_Rotation; }

		void setRotation(float angle) { m_Rotation = angle; recalculateMatrices(); }

		void setProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

		void setPosition(const glm::vec3& position) { m_Position = position; recalculateMatrices(); }
		void setPosition(float x, float y, float z) { m_Position.x = x; m_Position.y = y; m_Position.z = z; recalculateMatrices(); }
	};

	class PerspectiveCamera : Camera {


	};
}