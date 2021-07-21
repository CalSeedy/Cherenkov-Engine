#pragma once
#include "Camera.h"
#include "Texture.h"

namespace Cherenkov {

	class Renderer2D {

	public:
		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		static void Quad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& colour, float_t rotation = 0.0f);
		static void Quad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& colour, const Ref<Texture2D>& texture, float_t rotation = 0.0f);
		static void Quad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture2D>& texture, float_t rotation = 0.0f);

		static void Quad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& colour, float_t rotation = 0.0f);
		static void Quad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& colour, const Ref<Texture2D>& texture, float_t rotation = 0.0f);
		static void Quad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture, float_t rotation = 0.0f);
	};
}