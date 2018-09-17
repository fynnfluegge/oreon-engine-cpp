#pragma once

#include <vulkan\vulkan.h>
#include "buffer.h"

namespace vk {

	class StagingBuffer : Buffer {
	public:
		StagingBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties,
			const void* pData);
	};
}
