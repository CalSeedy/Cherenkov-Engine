#pragma once
#include "Cherenkov/Core/Core.h"

namespace Cherenkov {

	struct Specification {
		uint32_t Width, Height, Samples = 1;
		
		bool swapChainTarget = false;
	};

	class Framebuffer {
	public:
		static Ref<Framebuffer> init(const Specification spec);

		virtual const Specification& getSpecification() const = 0;
		virtual const uint32_t& getColourAttachment() const = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;
	};

}