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
		Ref<Shader> textureShader;
		Ref<Texture2D> Blank;
	};

	static Scope<Storage> s_Storage;

	void Renderer2D::init()	{
		CK_PROFILE_FUNCTION();
		s_Storage = CreateScope<Storage>();
		s_Storage->vertexArray = VertexArray::init();

		float verts[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0
		};

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::init(verts, sizeof(verts) / sizeof(float_t));

		BufferLayout layout = {
			{ShaderDataType::Vec3f, "a_Pos"},
			{ShaderDataType::Vec2f, "a_TexCoord"}
		};
		vertexBuffer->setLayout(layout);
		s_Storage->vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t idxs[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> indexBuffer = IndexBuffer::init(idxs, sizeof(idxs) / sizeof(uint32_t));
		s_Storage->vertexArray->setIndexBuffer(indexBuffer);
		{
			CK_PROFILE_SCOPE("Blank Texture");
			s_Storage->Blank = Texture2D::init(1, 1);
			uint32_t blankData = 0xffffffff;
			s_Storage->Blank->setData(&blankData, sizeof(blankData));
		}
		{
			CK_PROFILE_SCOPE("Texture Shader");
			s_Storage->textureShader = Shader::init("assets/Shaders/Texture.glsl");
			s_Storage->textureShader->bind();
			s_Storage->textureShader->setInt("tex", 0);
		}
	}

	void Renderer2D::shutdown()	{
		CK_PROFILE_FUNCTION();
		s_Storage.reset(nullptr);
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		CK_PROFILE_FUNCTION();
		s_Storage->textureShader->bind();
		s_Storage->textureShader->setMat4("viewProjection", camera.getViewProjection());
	}

	void Renderer2D::endScene() {
		CK_PROFILE_FUNCTION();
	}

	void Renderer2D::Quad(const glm::vec2& scale, const QuadProperties& properties) {
		Quad(scale, s_Storage->Blank, properties);
	}

	// all other Quads call this with default values
	void Renderer2D::Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties) {
		CK_PROFILE_FUNCTION();
		s_Storage->textureShader->setFloat4("colour", properties.Colour);
		s_Storage->textureShader->setFloat("tilingFactor", properties.TileFactor);

		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { properties.Position.x, properties.Position.y, properties.zPosition }) * glm::rotate(glm::mat4(1.0f), glm::radians(properties.Rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Storage->textureShader->setMat4("transform", transform);


		s_Storage->vertexArray->bind();
		RenderCommand::drawIndexed(s_Storage->vertexArray);
	}
}


