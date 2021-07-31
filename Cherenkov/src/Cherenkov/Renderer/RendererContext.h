#pragma once

namespace Cherenkov {
	class RendererContext {

	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
		virtual ~RendererContext() = default;

		static Scope<RendererContext> create(void* window);
	};
}