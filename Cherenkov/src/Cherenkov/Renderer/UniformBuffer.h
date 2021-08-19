#pragma once

#include "Cherenkov/Core/Core.h"

namespace Cherenkov {

	class UniformBuffer {
	public:
		virtual ~UniformBuffer() {}
		virtual void setData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static Ref<UniformBuffer> init(uint32_t size, uint32_t binding);
	};
}
