#include "ckpch.h"
#include "Renderer2D.h"

#include "Commands.h"
#include "Shader.h"

#include "Cherenkov/Core/Core.h"

#include "Cherenkov/Renderer/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Cherenkov {

	struct Storage {

		Ref<VertexArray> vertexArray;
		Ref<Shader> colourShader;
		Ref<Shader> textureShader;
	};

	static Scope<Storage> s_Storage;

	void Renderer2D::init()	{
		s_Storage = CreateScope<Storage>();
		s_Storage->vertexArray = VertexArray::init();

		float verts[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0
		};

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::init(verts, sizeof(verts) / sizeof(float_t)));

		BufferLayout layout = {
			{ShaderDataType::Vec3f, "a_Pos"},
			{ShaderDataType::Vec2f, "a_TexCoord"}
		};
		vertexBuffer->layout(layout);
		s_Storage->vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t idxs[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::init(idxs, sizeof(idxs) / sizeof(uint32_t)));
		s_Storage->vertexArray->setIndexBuffer(indexBuffer);

		std::string vertIn("../Cherenkov/src/Cherenkov/Shaders/shader.vert");
		std::string fragIn("../Cherenkov/src/Cherenkov/Shaders/shader.frag");

		s_Storage->colourShader = Shader::init("SquareColourShader", vertIn, fragIn);
		s_Storage->textureShader = Shader::init("assets/Shaders/Texture.glsl");
		s_Storage->textureShader->bind();
		s_Storage->textureShader->setInt("tex", 0);
	}

	void Renderer2D::shutdown()	{
		s_Storage.reset(nullptr);
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		s_Storage->colourShader->bind();
		s_Storage->colourShader->setMat4("viewProjection", camera.getViewProjection());
		
		s_Storage->textureShader->bind();
		s_Storage->textureShader->setMat4("viewProjection", camera.getViewProjection());
	}

	void Renderer2D::endScene() {

	}

	void Renderer2D::Quad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& colour, float_t rotation) {
		Quad({ position.x, position.y, 0.0f }, scale, colour, rotation);
	}

	void Renderer2D::Quad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& colour, const Ref<Texture2D>& texture, float_t rotation) {
		Quad({position.x, position.y, 0.0f}, scale, colour, texture, rotation);
	}

	void Renderer2D::Quad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& colour, float_t rotation) {
		s_Storage->colourShader->bind();
		s_Storage->colourShader->setFloat4("colour", colour);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Storage->colourShader->setMat4("transform", transform);
		s_Storage->vertexArray->bind();
		RenderCommand::drawIndexed(s_Storage->vertexArray);
	}

	void Renderer2D::Quad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& colour, const Ref<Texture2D>& texture, float_t rotation) {
		/*
		s_Storage->colourShader->bind();
		s_Storage->colourShader->setFloat4("colour", colour);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Storage->colourShader->setMat4("transform", transform);
		s_Storage->vertexArray->bind();
		RenderCommand::drawIndexed(s_Storage->vertexArray);
		*/
	}

	void Renderer2D::Quad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture2D>& texture, float_t rotation) {
		Quad({ position.x, position.y, 0.0f }, scale, texture, rotation);
	}

	void Renderer2D::Quad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture, float_t rotation) {
		s_Storage->textureShader->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Storage->textureShader->setMat4("transform", transform);

		texture->bind();

		s_Storage->vertexArray->bind();
		RenderCommand::drawIndexed(s_Storage->vertexArray);
	}


}


