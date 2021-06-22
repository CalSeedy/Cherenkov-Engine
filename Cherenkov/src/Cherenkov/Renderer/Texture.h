#pragma once
#include "Cherenkov/Core.h"

namespace Cherenkov {
	
	class Texture {


	public:
		virtual uint32_t width() const = 0;
		virtual uint32_t height() const = 0;
		
		
		virtual void bind(uint32_t slot = 0) const = 0;
	};


	class Texture2D : public Texture {

	public:
		static Ref<Texture2D> init(const std::string& path);
		virtual ~Texture2D() = default;
	};
}