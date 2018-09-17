#pragma once

#include <vulkan\vulkan.h>
#include "wrapper\device_local_buffer.h"
#include "command_pool.h"
#include "commandbuffer.h"

namespace vk {

	DeviceLocalBuffer& createDeviceLocalBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties,
		CommandPool commandPool, VkQueue queue, VkBufferUsageFlags usage, uint64_t size, const void* pData);
}
