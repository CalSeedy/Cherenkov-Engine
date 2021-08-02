#include "ckpch.h"
#include "Cherenkov/Renderer/Renderer2D.h"

#include "Cherenkov/Renderer/VertexArray.h"
#include "Cherenkov/Renderer/Shader.h"
#include "Cherenkov/Renderer/Commands.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Cherenkov {

	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TextureCoord;
		float TextureIdx;
		float TilingFactor;
	};

	struct Storage {
		static const uint32_t maxQuads = 10000;
		CK_CORE_ASSERT(maxQuads * 6 <= UINT32_MAX, "Maximum Quads exceeds the maximum value for uint32_t!");
		static const uint32_t maxVertices  = maxQuads * 4;
		static const uint32_t maxIndices   = maxQuads * 6;
		static const uint32_t maxTextures = 32;
		
		uint32_t quadIndices = 0;
		
		Ref<VertexArray> quadVertexArray;
		Ref<VertexBuffer> quadVertexBuffer;
		Ref<Shader> textureShader;
		Ref<Texture2D> Blank;

		QuadVertex* quadVertBufferBase = nullptr;
		QuadVertex* quadVertBufferPtr = nullptr;

		std::array<Ref<Texture2D>, maxTextures> boundTextures;
		uint32_t textureSlotIdx = 1;	// ^^ 0 - blank texture/ colour!

		glm::vec4 quadVertexPositions[4];

		Renderer2D::Statistics stats;
	};

	static Storage s_Storage;

	void Renderer2D::init()	{
		CK_PROFILE_FUNCTION();
		s_Storage.quadVertexArray = VertexArray::init();

		s_Storage.quadVertexBuffer = VertexBuffer::init(s_Storage.maxVertices * sizeof(QuadVertex));

		s_Storage.quadVertexBuffer->setLayout({
			{ShaderDataType::Vec3f, "in_Position"},
			{ShaderDataType::Vec4f, "in_Colour"},
			{ShaderDataType::Vec2f, "in_TextureCoord"},
			{ShaderDataType::Float, "in_TextureIdx"},
			{ShaderDataType::Float, "in_TilingFactor"}
			});
		s_Storage.quadVertexArray->addVertexBuffer(s_Storage.quadVertexBuffer);

		s_Storage.quadVertBufferBase = new QuadVertex[s_Storage.maxVertices];

		uint32_t* quadIndices = new uint32_t[s_Storage.maxIndices];
		
		uint32_t off = 0;
		for (uint32_t i = 0; i < s_Storage.maxIndices; i += 6) {
			quadIndices[i + 0] = off + 0;
			quadIndices[i + 1] = off + 1;
			quadIndices[i + 2] = off + 2;
			quadIndices[i + 3] = off + 2;
			quadIndices[i + 4] = off + 3;
			quadIndices[i + 5] = off + 0;

			off += 4;
		}

		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::init(quadIndices, s_Storage.maxIndices);
		s_Storage.quadVertexArray->setIndexBuffer(quadIndexBuffer);

		delete[] quadIndices;
		{
			CK_PROFILE_SCOPE("Blank Texture");
			s_Storage.Blank = Texture2D::init(1, 1);
			uint32_t blankData = 0xffffffff;
			s_Storage.Blank->setData(&blankData, sizeof(blankData));
		}
		int32_t textures [s_Storage.maxTextures];
		for (int32_t i = 0; i < s_Storage.maxTextures; i++) textures[i] = i;
		{
			CK_PROFILE_SCOPE("Texture Shader");
			s_Storage.textureShader = Shader::init("assets/Shaders/Texture.glsl");
			s_Storage.textureShader->bind();
			s_Storage.textureShader->setIntArray("textures", textures, s_Storage.maxTextures);

			s_Storage.boundTextures[0] = s_Storage.Blank;
		}

		s_Storage.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Storage.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Storage.quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Storage.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	}

	void Renderer2D::shutdown()	{
		CK_PROFILE_FUNCTION();

		delete[] s_Storage.quadVertBufferBase;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		CK_PROFILE_FUNCTION();
		s_Storage.textureShader->bind();
		s_Storage.textureShader->setMat4("viewProjection", camera.getViewProjection());

		s_Storage.quadIndices = 0;
		s_Storage.quadVertBufferPtr = s_Storage.quadVertBufferBase;

		s_Storage.textureSlotIdx = 1;
	}

	void Renderer2D::flush() {
		CK_PROFILE_FUNCTION();
		if (s_Storage.quadIndices == 0) return;
		for (uint32_t i = 0; i < s_Storage.textureSlotIdx; i++) s_Storage.boundTextures[i]->bind(i);
		RenderCommand::drawIndexed(s_Storage.quadVertexArray, s_Storage.quadIndices);
		s_Storage.stats.draws++;
	}

	void Renderer2D::flushAndReset() {
		endScene();
		s_Storage.quadIndices = 0;
		s_Storage.quadVertBufferPtr = s_Storage.quadVertBufferBase;
		s_Storage.textureSlotIdx = 1;
	}

	void Renderer2D::endScene() {
		CK_PROFILE_FUNCTION();
		uint32_t size = (uint32_t)((uint8_t*)s_Storage.quadVertBufferPtr - (uint8_t*)s_Storage.quadVertBufferBase);
		s_Storage.quadVertexBuffer->loadData(s_Storage.quadVertBufferBase, size);

		flush();
	}

	void Renderer2D::Quad(const glm::vec2& scale, const QuadProperties& properties) {
		Quad(scale, s_Storage.Blank, properties);
	}

	void Renderer2D::Quad(const glm::vec2& scale, const Ref<Texture2D>& texture, const QuadProperties& properties) {
		CK_PROFILE_FUNCTION();
		
		glm::mat4 transform = glm::mat4(1.0f);
		//	Translation
		if ((properties.Position.x != 0.0f) || (properties.Position.y != 0.0f) || (properties.Position.z != 0.0f)) {
			transform *= glm::translate(glm::mat4(1.0f), { properties.Position.x, properties.Position.y, properties.Position.z });
		}
		//	Rotation
		if (properties.Angle != 0.0f) {
			transform *= glm::rotate(glm::mat4(1.0f), properties.Angle, { 0.0f, 0.0f,1.0f });
		}
		//	Scale
		if ((scale.x != 1.0f) || (scale.y != 1.0f)) {
			transform *= glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		}

		Quad(transform, texture, properties.Colour, properties.TileFactor);
	}

	void Renderer2D::Quad(const glm::mat4& transform, glm::vec4 colour) {
		Quad(transform, s_Storage.Blank, colour);
	}

	// all other Quads eventually call this
	void Renderer2D::Quad(const glm::mat4& transform, const Ref<Texture2D>& texture, glm::vec4 colour, float_t tileFactor) {
		CK_PROFILE_FUNCTION();
		if (s_Storage.quadIndices >= Storage::maxIndices) flushAndReset();
		constexpr glm::vec2 quadDefaultTexCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Storage.textureSlotIdx; i++) {
			if (*s_Storage.boundTextures[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {

			if (s_Storage.textureSlotIdx >= Storage::maxTextures) flushAndReset();

			textureIndex = (float)s_Storage.textureSlotIdx;
			s_Storage.boundTextures[s_Storage.textureSlotIdx] = texture;
			s_Storage.textureSlotIdx++;
		}

		for (int i = 0; i < 4; i++) {
			s_Storage.quadVertBufferPtr->Position = transform * s_Storage.quadVertexPositions[i];
			s_Storage.quadVertBufferPtr->Colour = colour;
			s_Storage.quadVertBufferPtr->TextureCoord = quadDefaultTexCoords[i];
			s_Storage.quadVertBufferPtr->TextureIdx = textureIndex;
			s_Storage.quadVertBufferPtr->TilingFactor = tileFactor;
			s_Storage.quadVertBufferPtr++;
		}

		s_Storage.quadIndices += 6;
		s_Storage.stats.quads++;
	}

	void Renderer2D::resetStats() {
		memset(&s_Storage.stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::getStats() { return s_Storage.stats; }
}


