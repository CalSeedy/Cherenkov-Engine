#include "ckpch.h"
#include "Cherenkov/Renderer/Commands.h"

namespace Cherenkov {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
