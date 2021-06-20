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

		virtual void setRotation(float angle) = 0;

		virtual void setPosition(const glm::vec3& position) = 0;
		virtual void setPosition(float x, float y, float z) = 0;
	};

	class OrthographicCamera : Camera {
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_Projection;
		
		float m_Rotation = 0.0f;
		glm::mat4 m_View;
		glm::mat4 m_ViewProjection;

		void recalculateMatrices() override;
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		inline const glm::mat4& getProjection() const override { return m_Projection; }
		inline const glm::mat4& getViewProjection() const override { return m_ViewProjection; }
		inline const glm::mat4& getView() const override { return m_View; }

		inline const glm::vec3& getPosition() const override {  return m_Position;  }
		inline const float& getRotation() const override { return m_Rotation; }

		inline void setRotation(float angle) { m_Rotation = angle; recalculateMatrices(); }

		inline void setPosition(const glm::vec3& position) override { m_Position = position; recalculateMatrices(); }
		inline void setPosition(float x, float y, float z) override { m_Position.x = x; m_Position.y = y; m_Position.z = z; recalculateMatrices(); }
	};

	class PerspectiveCamera : Camera {


	};
}