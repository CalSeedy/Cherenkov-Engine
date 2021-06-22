#include "ckpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
namespace Cherenkov {
	
	Renderer::Scene* Renderer::s_Scene = new Renderer::Scene;

	void Renderer::beginScene(OrthographicCamera& camera) {
		s_Scene->Projection = camera.getViewProjection();
	}

	void Renderer::endScene() {

	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniformMat4("viewProjection", s_Scene->Projection);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uniformMat4("transform", transform);
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}

}