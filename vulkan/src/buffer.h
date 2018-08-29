#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class Buffer {
	public:
		Buffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage);
		void allocate(VkPhysicalDeviceMemoryProperties memoryProperties,
			VkMemoryPropertyFlags memoryPropertyFlags);
		void bindBufferMemory();
		void mapMemory(const void* data);
		void destroy();
	private:
		VkBuffer handle;
		VkDeviceMemory memory;
		const VkDevice device;
		uint64_t size;
	};
}
