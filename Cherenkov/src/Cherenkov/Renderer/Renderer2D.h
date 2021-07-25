#pragma once
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Renderer/Texture.h"

namespace Cherenkov {

	struct QuadProperties {
		union X {
			struct {
				float_t x, y, z;
			};
			X() { x = 0.0f; y = 0.0f; z = 0.0f; }
			X(glm::vec2 pos) { x = pos.x; y = pos.y; z = 0.0f; }
			X(glm::vec3 pos) { x = pos.x; y = pos.y; z = pos.z; }
			X(float_t _x, float_t _y) { x = _x; y = _y; z = 0.0f; }
			X(float_t _x, float_t _y, float_t _z) { x = _x; y = _y; z = _z; }
		} Position = {};
		glm::vec4 Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		float_t Rotation = 0.0f;
		float_t TileFactor = 1.0f;
	};

	class Renderer2D {

	public:
		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void flush();
		static void endScene();

		static void Quad(const glm::vec2& scale, const QuadProperties& properties = QuadProperties());
		static void Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties = QuadProperties());
	};
}