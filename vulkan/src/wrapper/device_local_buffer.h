#pragma once

#include <vulkan\vulkan.h>
#include "buffer.h"

namespace vk {

	class DeviceLocalBuffer : Buffer{
	public:
		DeviceLocalBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties,
			uint64_t size, VkBufferUsageFlags usageFlags);
	};
}
