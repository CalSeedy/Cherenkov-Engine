#pragma once
#include "Cherenkov/Core/Core.h"

namespace Cherenkov {

	struct FbSpecification {
		uint32_t Width = 0 , Height = 0, Samples = 1;
		
		bool swapChainTarget = false;
	};

	class Framebuffer {
	public:
		static Ref<Framebuffer> init(const FbSpecification spec);
		virtual ~Framebuffer() = default;

		virtual const FbSpecification& getSpecification() const = 0;
		virtual const uint32_t& getColourAttachment() const = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;
	};

}
