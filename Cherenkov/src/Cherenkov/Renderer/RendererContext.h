#pragma once

namespace Cherenkov {
	class RendererContext {

	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
		virtual void setViewport(uint32_t width, uint32_t height) const = 0;
	};
}