#pragma once
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Renderer/Commands.h"
#include "Cherenkov/Renderer/Shader.h"

namespace Cherenkov {

	class Renderer {
		struct Scene {
			glm::mat4 Projection;
		};
		static Scope<Scene> s_Scene;

	public:
		static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

		static void init();
		static void shutdown();
		static void beginScene(OrthographicCamera& camera);
		static void endScene();
		static void submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void onWindowResize(uint32_t width, uint32_t height);
	};
	
}