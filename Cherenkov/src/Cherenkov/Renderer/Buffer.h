#pragma once

namespace Cherenkov {

	enum struct ShaderDataType {
		None = 0, Float, Int, Bool, Struct,

		Vec2f, Vec3f, Vec4f, 
		Mat2f, Mat3f, Mat4f,

		Vec2i, Vec3i, Vec4i,
		Mat2i, Mat3i, Mat4i

	};

	static uint32_t TypeSize(ShaderDataType type) {
		switch (type)
		{
		case Cherenkov::ShaderDataType::None:			return 0;
		case Cherenkov::ShaderDataType::Float:			return sizeof(float);
		case Cherenkov::ShaderDataType::Int:			return sizeof(int);
		case Cherenkov::ShaderDataType::Bool:			return sizeof(bool);
		//case Cherenkov::ShaderDataType::Struct:			return sizeof(struct);
		case Cherenkov::ShaderDataType::Vec2f:			return 2 * sizeof(float);
		case Cherenkov::ShaderDataType::Vec3f:			return 3 * sizeof(float);
		case Cherenkov::ShaderDataType::Vec4f:			return 4 * sizeof(float);
		case Cherenkov::ShaderDataType::Mat2f:			return 2 * 2 * sizeof(float);
		case Cherenkov::ShaderDataType::Mat3f:			return 4 * 3 * sizeof(float);
		case Cherenkov::ShaderDataType::Mat4f:			return 4 * 4 * sizeof(float);
		case Cherenkov::ShaderDataType::Vec2i:			return 2 * sizeof(int);
		case Cherenkov::ShaderDataType::Vec3i:			return 3 * sizeof(int);
		case Cherenkov::ShaderDataType::Vec4i:			return 4 * sizeof(int);
		case Cherenkov::ShaderDataType::Mat2i:			return 2 * 2 * sizeof(int);
		case Cherenkov::ShaderDataType::Mat3i:			return 4 * 3 * sizeof(int);
		case Cherenkov::ShaderDataType::Mat4i:			return 4 * 4 * sizeof(int);
		default:
			CK_CORE_ASSERT(false, "Unknown DataType {0}!", type);
			return 0;
		}
	}

	struct BufferElement {
		std::string Identifier;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalised;
		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string name, bool normalised = false) : Identifier{ name }, Type{ type }, Size{ TypeSize(type) }, Offset{ 0 }, Normalised{ normalised }{
		}

		uint32_t count() const {
			switch (Type)
			{
			case Cherenkov::ShaderDataType::None:				return 0;
			case Cherenkov::ShaderDataType::Float:				return 1;
			case Cherenkov::ShaderDataType::Int:				return 1;
			case Cherenkov::ShaderDataType::Bool:				return 1;
			//case Cherenkov::ShaderDataType::Struct:			break;
			case Cherenkov::ShaderDataType::Vec2f:				return 2;
			case Cherenkov::ShaderDataType::Vec3f:				return 3;
			case Cherenkov::ShaderDataType::Vec4f:				return 4;
			case Cherenkov::ShaderDataType::Mat2f:				return 4;
			case Cherenkov::ShaderDataType::Mat3f:				return 9;
			case Cherenkov::ShaderDataType::Mat4f:				return 16;
			case Cherenkov::ShaderDataType::Vec2i:				return 2;
			case Cherenkov::ShaderDataType::Vec3i:				return 3;
			case Cherenkov::ShaderDataType::Vec4i:				return 4;
			case Cherenkov::ShaderDataType::Mat2i:				return 4;
			case Cherenkov::ShaderDataType::Mat3i:				return 9;
			case Cherenkov::ShaderDataType::Mat4i:				return 16;
			default:
				CK_CORE_ASSERT(false, "Unknown DataType {0}!", type);
				return 0;
			}
		}
	};

	class BufferLayout {
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
		inline void calculateOffsets() {
			uint32_t offset = 0;
			for (auto& e : m_Elements) {
				e.Offset = offset;
				offset += e.Size;
				m_Stride += e.Size;
			}
		}
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements{ elements } { calculateOffsets(); }
		inline std::vector<BufferElement>& elements() { return m_Elements; }
		inline uint32_t stride() const { return m_Stride; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	class VertexBuffer {
		std::vector<float> m_Data;
	public:

		void loadData(std::vector<float> data);

		virtual void bind()	const = 0;
		virtual void unbind() const = 0;
		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static Ref<VertexBuffer> init(float_t* vertices, uint32_t count);

		virtual ~VertexBuffer() = default;
	};

	class IndexBuffer {
		std::vector<unsigned int> m_Data;
	public:

		void loadData(std::vector<unsigned int> data);

		virtual void bind()	const = 0;
		virtual void unbind() const = 0;
		virtual uint32_t count() const = 0;

		static Ref<IndexBuffer> init(uint32_t* indices, uint32_t count);


		virtual ~IndexBuffer() = default;
	};
}