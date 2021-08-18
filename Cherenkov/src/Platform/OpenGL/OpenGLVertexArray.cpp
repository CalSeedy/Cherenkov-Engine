#include "ckpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

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
		default:										CK_CORE_ASSERT(false, "Unknown DataType!");	return 0;
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

		const auto& layout = vBuffer->getLayout();
		uint8_t count;
		for (auto& element : layout) {
			switch (element.Type) {
			case Cherenkov::ShaderDataType::None:	
			//case Cherenkov::ShaderDataType::Struct
			case Cherenkov::ShaderDataType::Float:	
			case Cherenkov::ShaderDataType::Vec2f:	
			case Cherenkov::ShaderDataType::Vec3f:	
			case Cherenkov::ShaderDataType::Vec4f:
				glEnableVertexAttribArray(m_VBufferIdx);
				glVertexAttribPointer(m_VBufferIdx, element.count(), getBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE, layout.stride(), (const void*)(uint64_t)(element.Offset));
				m_VBufferIdx++;
				break;
			case Cherenkov::ShaderDataType::Bool:
			case Cherenkov::ShaderDataType::Int:
			case Cherenkov::ShaderDataType::Vec2i:
			case Cherenkov::ShaderDataType::Vec3i:
			case Cherenkov::ShaderDataType::Vec4i:
				glEnableVertexAttribArray(m_VBufferIdx);
				glVertexAttribIPointer(m_VBufferIdx, element.count(), getBaseType(element.Type), layout.stride(), (const void*)(uint64_t)(element.Offset));
				m_VBufferIdx++;
				break;
			case Cherenkov::ShaderDataType::Mat2f:
			case Cherenkov::ShaderDataType::Mat3f:
			case Cherenkov::ShaderDataType::Mat4f:
				count = element.count();
				for (uint8_t i = 0; i < count; i++) {
					glEnableVertexAttribArray(m_VBufferIdx);
					glVertexAttribPointer(m_VBufferIdx, count, getBaseType(element.Type), element.Normalised ? GL_TRUE : GL_FALSE, layout.stride(), (const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VBufferIdx, 1);
					m_VBufferIdx++;
				}
				break;
			case Cherenkov::ShaderDataType::Mat2i:
			case Cherenkov::ShaderDataType::Mat3i:
			case Cherenkov::ShaderDataType::Mat4i: {
				count = element.count();
				for (uint8_t i = 0; i < count; i++) {
					glEnableVertexAttribArray(m_VBufferIdx);
					glVertexAttribIPointer(m_VBufferIdx, count, getBaseType(element.Type), layout.stride(), (const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VBufferIdx, 1);
					m_VBufferIdx++;
				}
				break;
			}
			default:								CK_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
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
