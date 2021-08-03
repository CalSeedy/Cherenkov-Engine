#pragma once
#include "Cherenkov/Renderer/Camera.h"

namespace Cherenkov {

	class SceneCamera : public Camera {
		float_t m_OrthographicSize = 10.0f;
		float_t m_OrthographicNear = -1.0f;
		float_t m_OrthographicFar = 1.0f;
		float_t m_AspectRatio = 1.0f;

		void recalculate();
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void setOrthographic(float_t size, float_t near, float_t far);
		void setViewport(uint32_t width, uint32_t height);

		void setOrthographicSize(float_t size) { m_OrthographicSize = size; recalculate(); }
		float_t getOrthographicSize() const { return m_OrthographicSize; }
	};
}