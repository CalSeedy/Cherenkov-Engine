#pragma once
#include "Camera.h"
#include "Texture.h"

namespace Cherenkov {

	struct QuadProperties {
		glm::vec2 Position = { 0.0f, 0.0f };
		glm::vec4 Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		float_t Rotation = 0.0f;
		float_t TileFactor = 1.0f;
		float_t zPosition = 0.0f;

	};

	class Renderer2D {

	public:
		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		static void Quad(const glm::vec2& scale, const QuadProperties& properties = QuadProperties());
		static void Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties = QuadProperties());
	};
}