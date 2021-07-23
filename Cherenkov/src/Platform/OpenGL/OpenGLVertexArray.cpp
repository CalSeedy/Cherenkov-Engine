#include "ckpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace Cherenkov {

	static GLenum getBaseType(ShaderDataType type) {
		switch (type)
		{
		case Cherenkov::ShaderDataType::None:			return GL_NONE;
		case Cherenkov::ShaderDataType::Float:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Int:			return GL_INT;
		case Cherenkov::ShaderDataType::Bool:			return GL_BOOL;
			//case Cherenkov::ShaderDataType::Struct:			break;
		case Cherenkov::ShaderDataType::Vec2f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec3f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec4f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat2f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat3f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Mat4f:			return GL_FLOAT;
		case Cherenkov::ShaderDataType::Vec2i:			return GL_INT;
		case Cherenkov::ShaderDataType::Vec3i:			return GL_INT;
		case Cherenkov::ShaderDataType::Vec4i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat2i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat3i:			return GL_INT;
		case Cherenkov::ShaderDataType::Mat4i:			return GL_INT;
		default:
			CK_CORE_ASSERT(false, "Unknown DataType {0}!", type);
			return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		CK_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const {
		CK_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::unbind() const{
		CK_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vBuffer) {
		CK_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		vBuffer->bind();

		CK_CORE_ASSERT(vBuffer->getLayout().elements().size(), "Empty vertex buffer layout!");

		uint32_t idx = 0;
		const auto& layout = vBuffer->getLayout();
		for (auto& element : layout) {
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, element.count(), getBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE, layout.stride(), (const void*)element.Offset);
			idx++;
		}
		m_VertexBuffers.push_back(vBuffer);
	}
	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& iBuffer){
		CK_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		iBuffer->bind();
		m_IndexBuffer = iBuffer;
	}

	OpenGLVertexArray::~OpenGLVertexArray()	{
		CK_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

}