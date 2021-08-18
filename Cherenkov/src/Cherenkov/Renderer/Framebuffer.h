#pragma once
#include "Cherenkov/Core/Core.h"

namespace Cherenkov {

	enum class FbTextureFormat {
		None = 0,

		RGBA8,
		RED_INT,

		DEPTH24STENCIL8,

		Depth = DEPTH24STENCIL8
	};

	struct FbTextureSpecification {

		FbTextureFormat TextureFormat = FbTextureFormat::None;

		FbTextureSpecification() = default;
		FbTextureSpecification(FbTextureFormat format) : TextureFormat{ format } {}

	};

	struct FbAttachmentSpecification {

		std::vector<FbTextureSpecification> Attachments;

		FbAttachmentSpecification() = default;
		FbAttachmentSpecification(std::initializer_list<FbTextureSpecification> attachments) : Attachments{ attachments } {}

	};


	struct FbSpecification {
		uint32_t Width = 0 , Height = 0, Samples = 1;
		FbAttachmentSpecification Attachments;
		bool swapChainTarget = false;
	};

	class Framebuffer {
	public:
		static Ref<Framebuffer> init(const FbSpecification spec);
		virtual ~Framebuffer() = default;

		virtual const FbSpecification& getSpecification() const = 0;
		virtual uint32_t getColourAttachment(uint32_t ind = 0) const = 0;
		virtual int readPixel(uint32_t attachmentID, int x, int y) = 0;

		virtual void clearColourAttachment(uint32_t idx, int data) = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		virtual void resize(uint32_t width, uint32_t height) = 0;
	};

}
