#include "device_local_buffer.h"

using namespace vk;

DeviceLocalBuffer::DeviceLocalBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties,
	uint64_t size, VkBufferUsageFlags usageFlags)
		: Buffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | usageFlags)
{
	allocate(memoryProperties, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	bindBufferMemory();
}
