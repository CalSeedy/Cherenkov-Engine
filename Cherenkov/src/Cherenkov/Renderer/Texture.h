#pragma once
#include <string>
#include "Cherenkov/Core/Core.h"

namespace Cherenkov {
	
	class Texture {
	public:
		virtual uint32_t width() const = 0;
		virtual uint32_t height() const = 0;
		
		
		virtual void bind(uint32_t slot = 0) const = 0;
		virtual void setData(void* data, uint32_t size) = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};


	class Texture2D : public Texture {

	public:
		static Ref<Texture2D> init(const std::string& path);
		static Ref<Texture2D> init(uint32_t width, uint32_t height);
		virtual ~Texture2D() = default;

		virtual void setData(void* data, uint32_t size) = 0;
		virtual bool operator==(const Texture& other) const = 0;
	};
}