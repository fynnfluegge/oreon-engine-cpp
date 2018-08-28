#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class Framebuffer {
	public:
		Framebuffer(VkDevice device, uint32_t width, uint32_t height, uint32_t layers,
			const VkImageView* pAttachments, VkRenderPass renderPass);
		void destroy();
	private:
		VkFramebuffer handle;
		const VkDevice device;
	};
}
