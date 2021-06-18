#pragma once

namespace Cherenkov {

	class VertexBuffer {
		std::vector<float> m_Data;
	public:

		void loadData(std::vector<float> data);

		virtual void bind()	const = 0;
		virtual void unbind() const = 0;

		static VertexBuffer* init(float_t* vertices, uint32_t count);

		virtual ~VertexBuffer() {}
	};

	class IndexBuffer {
		std::vector<unsigned int> m_Data;
	public:

		void loadData(std::vector<unsigned int> data);

		virtual void bind()	const = 0;
		virtual void unbind() const = 0;
		virtual uint32_t count() const = 0;

		static IndexBuffer* init(uint32_t* indices, uint32_t count);


		virtual ~IndexBuffer() {}
	};
}