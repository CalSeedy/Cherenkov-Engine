#include "ckpch.h"
#include "Cherenkov/Renderer/Renderer.h"
#include "Cherenkov/Renderer/Renderer2D.h"


namespace Cherenkov {
	
	Scope<Renderer::Scene> Renderer::s_Scene = CreateScope<Renderer::Scene>();

	void Renderer::init() {
		CK_PROFILE_FUNCTION();
		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::shutdown() {
		Renderer2D::shutdown();
	}

	void Renderer::beginScene(OrthographicCamera& camera) {
		s_Scene->Projection = camera.getViewProjection();
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
		shader->bind();
		shader->setMat4("viewProjection", s_Scene->Projection);
		shader->setMat4("transform", transform);
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}

	void Renderer::onWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::setViewport(0, 0, width, height);
	}

}