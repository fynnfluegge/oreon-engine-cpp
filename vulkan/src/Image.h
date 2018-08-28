#pragma once

#include <vulkan\vulkan.h>
#include <stb_image.h>

namespace vk {

	class Image {
	public:
		Image(VkDevice device, uint32_t width, uint32_t height, uint32_t depth,
			VkFormat format, VkImageUsageFlags usage, uint32_t samples, uint32_t mipLevels);
		void allocate(VkPhysicalDeviceMemoryProperties memoryProperties,
			VkMemoryPropertyFlags memoryPropertyFlags);
		void bindImageMemory();
		void mapMemory(stbi_uc* pixels);
		void destroy();
	private:
		VkImage handle;
		VkDeviceMemory memory;
		int format;
		VkDeviceSize allocationSize;
		const VkDevice device;
	};
}
