#pragma once
#include <glm/glm.hpp>

namespace Cherenkov {

	class Camera {
		virtual void recalculateMatrices() = 0;
	public:

		virtual const glm::mat4& getProjection() const = 0;
		virtual const glm::mat4& getViewProjection() const = 0;
		virtual const glm::mat4& getView() const = 0;
		
		virtual const glm::vec3& getPosition() const = 0;
		virtual const float& getRotation() const = 0;

		virtual void setRotation(float x, float y, float z) = 0;
		virtual void setRotation(const glm::vec3& rotation) = 0;

		virtual void setPosition(const glm::vec3& position) = 0;
	};

	class OrthographicCamera : Camera {
		glm::vec3 m_Position;
		glm::mat4 m_Projection;
		glm::vec3 m_Rotation;
		
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		void recalculateMatrices() override;
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		inline const glm::mat4& getProjection() const override { return m_Projection; }
		inline const glm::mat4& getViewProjection() const override { return m_ViewProjection; }
		inline const glm::mat4& getView() const override { return m_View; }

		inline const glm::vec3& getPosition() const override {  return m_Position;  }
		inline const float& getRotation() const override { return m_Rotation.z; }

		inline void setRotation(const glm::vec3& rotation) override {
			m_Rotation.x = rotation.x; m_Rotation.y = rotation.y; m_Rotation.z = rotation.z; recalculateMatrices();
		}

		inline void setRotation(float x, float y, float z) override {
			m_Rotation.x = x; m_Rotation.y = y; m_Rotation.z = z; recalculateMatrices();
		}
		inline void setRotation(float z) { setRotation(0.0f, 0.0f, z); }

		inline void setPosition(const glm::vec3& position) override { m_Position = position; recalculateMatrices(); }
	};

	class PerspectiveCamera : Camera {


	};
}