#pragma once
#include "Cherenkov/Renderer/Camera.h"

namespace Cherenkov {

	static const char* projectionTypes[] = {"Orthographic", "Perspective"};

	enum class ProjectionType {
		Orthographic = 0,
		Perspective = 1
	};

	class SceneCamera : public Camera {
		float_t m_OrthographicSize = 10.0f;
		float_t m_OrthographicNear = -1.0f;
		float_t m_OrthographicFar = 1.0f;
		float_t m_AspectRatio = 1.0f;

		float_t m_PerspectiveFOV = 45.0f;
		float_t m_PerspectiveNear = 0.01f;
		float_t m_PerspectiveFar = 1000.0f;

		ProjectionType m_Type = ProjectionType::Orthographic;

		void recalculate();
		friend class EntityProperties;
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;
		
		void setProperties(float_t aspect, float_t orthoSize, float_t orthoNear, float_t orthoFar, float_t perspFOV, float_t perspNear, float_t perspFar);
		void setPerspective(float_t fov, float_t near, float_t far);
		void setOrthographic(float_t size, float_t near, float_t far);
		void setViewport(uint32_t width, uint32_t height);
		void setOrthographicSize(float_t size) { m_OrthographicSize = size; recalculate(); }

		float_t getAspectRatio() const { return m_AspectRatio; }
		float_t getOrthographicSize() const { return m_OrthographicSize; }
		float_t getOrthographicNear() const { return m_OrthographicNear; }
		float_t getOrthographicFar() const { return m_OrthographicFar; }
		float_t getPerspectiveFOV() const { return m_PerspectiveFOV; }
		float_t getPerspectiveNear() const { return m_PerspectiveNear; }
		float_t getPerspectiveFar() const { return m_PerspectiveFar; }
		
		void setType(const ProjectionType type);
		ProjectionType getType() { return m_Type; }
		std::string getTypeName() const { return projectionTypes[(uint32_t)m_Type]; }
	};
}
