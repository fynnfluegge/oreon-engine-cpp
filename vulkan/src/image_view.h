#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class ImageView {
	public:
		ImageView(VkDevice device, VkFormat format, VkImage image,
			VkImageAspectFlags aspectMask, uint32_t mipLevels);
		void destroy();
	private:
		VkImageView handle;
		const VkDevice device;
	};

}
