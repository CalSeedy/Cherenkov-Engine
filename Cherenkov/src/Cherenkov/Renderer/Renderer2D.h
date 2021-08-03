#pragma once
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Renderer/Texture.h"

namespace Cherenkov {
	struct QuadProperties {
		struct Pos {
			union {
				struct {
					float_t x, y, z;
				};
				glm::vec3 position;
			};

			Pos() { x = 0.0f; y = 0.0f; z = 0.0f; }
			Pos(const glm::vec2& pos) { x = pos.x; y = pos.y; z = 0.0f; position = { pos.x, pos.y, 0.0f }; }
			Pos(const glm::vec3& pos) { x = pos.x; y = pos.y; z = pos.z; position = pos; }
			Pos(float_t _x, float_t _y) { x = _x; y = _y; z = 0.0f; }
			Pos(float_t _x, float_t _y, float_t _z) { x = _x; y = _y; z = _z; }

			operator glm::vec3& () { return position; }
			operator const glm::vec3& () const { return position; }
		} Position = {};
		glm::vec4 Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		float_t Angle = 0.0f;
		float_t TileFactor = 1.0f;
	};

	class Renderer2D {
		static void flushAndReset();
	public:
		struct RendererCamera
		{
			glm::mat4 Projection;
			glm::mat4 View;
		};

		static void init();
		static void shutdown();

		static void beginScene(const Camera& camera, const glm::mat4& transform);
		static void beginScene(const OrthographicCamera& camera);
		static void flush();
		static void endScene();

		static void Quad(const glm::vec2& scale, const QuadProperties& properties = QuadProperties());
		static void Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties = QuadProperties());
		static void Quad(const glm::mat4& transform, glm::vec4 colour);
		static void Quad(const glm::mat4& transform, const Ref<Texture2D>& texture, glm::vec4 colour = { 1.0f, 1.0f, 1.0f, 1.0f }, float_t tileFactor = 1.0f);

		struct Statistics {
			uint32_t draws = 0;
			uint32_t quads = 0;

			uint32_t getTotalVertices() { return quads * 4; }
			uint32_t getTotalIndices() { return quads * 6; }
		};
		static void resetStats();
		static Statistics getStats();
	};
}