#include "ckpch.h"
#include "Commands.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cherenkov {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
