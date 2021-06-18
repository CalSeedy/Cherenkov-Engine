#pragma once
#include "Cherenkov/Core.h"

namespace Cherenkov {

	class Shader {

	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}