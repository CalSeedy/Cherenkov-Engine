#pragma once
#include "Camera.h"
#include "Commands.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
namespace Cherenkov {

	class Renderer {
		struct Scene {
			glm::mat4 Projection;
		};
		static Scene* s_Scene;
	public:
		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

		static void beginScene(OrthographicCamera& camera);
		static void endScene();
		static void submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
	};
	
}