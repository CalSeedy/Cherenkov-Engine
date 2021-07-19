#include "ckpch.h"
#include "Commands.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cherenkov {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}
