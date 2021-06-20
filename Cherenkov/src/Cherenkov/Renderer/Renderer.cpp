#include "ckpch.h"
#include "Renderer.h"

namespace Cherenkov {
	
	Renderer::Scene* Renderer::m_Scene = new Renderer::Scene;

	void Renderer::beginScene(OrthographicCamera& camera) {
		m_Scene->Projection = camera.getViewProjection();
	}

	void Renderer::endScene() {

	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
		shader->bind();
		shader->uniformMat4("viewProjection", m_Scene->Projection);
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}

}