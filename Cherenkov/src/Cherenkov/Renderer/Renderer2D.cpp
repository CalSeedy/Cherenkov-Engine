#include "ckpch.h"
#include "Cherenkov/Renderer/Renderer2D.h"

#include "Cherenkov/Renderer/VertexArray.h"
#include "Cherenkov/Renderer/Shader.h"
#include "Cherenkov/Renderer/Commands.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define maxQuads 5
#if maxQuads*6 >= UINT32_MAX
CK_CORE_ASSERT(false, "Maximum Quads exceeds the maximum value for uint32_t!");
#else
#define maxVertices maxQuads * 4
#define maxIndices  maxQuads * 6
#endif

namespace Cherenkov {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TextureCoord;
	};

	struct Storage {
		
		uint32_t quadIndices = 0;
		
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> Blank;

		QuadVertex* quadVertBufferBase = nullptr;
		QuadVertex* quadVertBufferPtr = nullptr;
	};

	static Storage s_Storage;

	void Renderer2D::init()	{
		CK_PROFILE_FUNCTION();
		s_Storage.quadVertexArray = VertexArray::init();

		s_Storage.quadVertexBuffer = VertexBuffer::init(maxVertices * sizeof(QuadVertex));

		s_Storage.quadVertexBuffer->setLayout({
			{ShaderDataType::Vec3f, "in_Position"},
			{ShaderDataType::Vec4f, "in_Colour"},
			{ShaderDataType::Vec2f, "in_TextureCoord"}
			});
		s_Storage.quadVertexArray->addVertexBuffer(s_Storage.quadVertexBuffer);

		s_Storage.quadVertBufferBase = new QuadVertex[maxVertices];

		uint32_t* quadIndices = new uint32_t[maxIndices];
		
		uint32_t off = 0;
		for (uint32_t i = 0; i < maxIndices; i += 6) {
			quadIndices[i + 0] = off + 0;
			quadIndices[i + 1] = off + 1;
			quadIndices[i + 2] = off + 2;
			quadIndices[i + 3] = off + 2;
			quadIndices[i + 4] = off + 3;
			quadIndices[i + 5] = off + 0;

			off += 4;
		}

		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::init(quadIndices, maxIndices);
		s_Storage.quadVertexArray->setIndexBuffer(quadIndexBuffer);

		delete[] quadIndices;
		{
			CK_PROFILE_SCOPE("Blank Texture");
			s_Storage.Blank = Texture2D::init(1, 1);
			uint32_t blankData = 0xffffffff;
			s_Storage.Blank->setData(&blankData, sizeof(blankData));
		}
		{
			CK_PROFILE_SCOPE("Texture Shader");
			s_Storage.textureShader = Shader::init("assets/Shaders/Texture.glsl");
			s_Storage.textureShader->bind();
			s_Storage.textureShader->setInt("tex", 0);
		}
	}

	void Renderer2D::shutdown()	{
		CK_PROFILE_FUNCTION();
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		CK_PROFILE_FUNCTION();
		s_Storage.textureShader->bind();
		s_Storage.textureShader->setMat4("viewProjection", camera.getViewProjection());

		s_Storage.quadIndices = 0;
		s_Storage.quadVertBufferPtr = s_Storage.quadVertBufferBase;
	}

	void Renderer2D::flush() {
		CK_PROFILE_FUNCTION();
		RenderCommand::drawIndexed(s_Storage.quadVertexArray, s_Storage.quadIndices);
	}

	void Renderer2D::endScene() {
		CK_PROFILE_FUNCTION();
		uint32_t size = (uint8_t*)s_Storage.quadVertBufferPtr - (uint8_t*)s_Storage.quadVertBufferBase;
		s_Storage.quadVertexBuffer->loadData(s_Storage.quadVertBufferBase, size);

		flush();
	}

	void Renderer2D::Quad(const glm::vec2& scale, const QuadProperties& properties) {
		Quad(scale, s_Storage.Blank, properties);
	}

	// all other Quads call this with default values
	void Renderer2D::Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties) {
		CK_PROFILE_FUNCTION();

		// Bottom Left
		s_Storage.quadVertBufferPtr->Position = { properties.Position.x, properties.Position.y, properties.Position.z };
		s_Storage.quadVertBufferPtr->Colour = properties.Colour;
		s_Storage.quadVertBufferPtr->TextureCoord = { 0.0f, 0.0f };
		s_Storage.quadVertBufferPtr++;

		//Bottom Right
		s_Storage.quadVertBufferPtr->Position = { properties.Position.x + scale.x, properties.Position.y, properties.Position.z };
		s_Storage.quadVertBufferPtr->Colour = properties.Colour;
		s_Storage.quadVertBufferPtr->TextureCoord = { 1.0f, 0.0f };
		s_Storage.quadVertBufferPtr++;

		// Top Right
		s_Storage.quadVertBufferPtr->Position = { properties.Position.x + scale.x, properties.Position.y + scale.y, properties.Position.z };
		s_Storage.quadVertBufferPtr->Colour = properties.Colour;
		s_Storage.quadVertBufferPtr->TextureCoord = { 1.0f, 1.0f };
		s_Storage.quadVertBufferPtr++;

		//Top Left
		s_Storage.quadVertBufferPtr->Position = { properties.Position.x, properties.Position.y + scale.y, properties.Position.z };
		s_Storage.quadVertBufferPtr->Colour = properties.Colour;
		s_Storage.quadVertBufferPtr->TextureCoord = { 0.0f, 1.0f };
		s_Storage.quadVertBufferPtr++;

		s_Storage.quadIndices += 6;
		/*
		s_Storage.textureShader->setFloat("tilingFactor", properties.TileFactor);

		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), s_Storage.quadVertBufferPtr->Position) * glm::rotate(glm::mat4(1.0f), glm::radians(properties.Rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		s_Storage.textureShader->setMat4("transform", transform);


		s_Storage.quadVertexArray->bind();
		RenderCommand::drawIndexed(s_Storage.quadVertexArray);
		*/
	}
}


