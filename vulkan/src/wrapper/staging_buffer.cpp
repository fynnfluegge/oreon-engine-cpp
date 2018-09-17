#include "staging_buffer.h"

using namespace vk;

StagingBuffer::StagingBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties, const void* pData)
	: Buffer(device, 1, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
{
	allocate(memoryProperties,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	bindBufferMemory();
	mapMemory(pData);
}
