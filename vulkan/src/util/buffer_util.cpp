#include "buffer_util.h"
#include "wrapper\staging_buffer.h"
#include "wrapper\device_local_buffer.h"

using namespace vk;

DeviceLocalBuffer& vk::createDeviceLocalBuffer(VkDevice device, VkPhysicalDeviceMemoryProperties memoryProperties,
	CommandPool commandPool, VkQueue queue, VkBufferUsageFlags usage, uint64_t size, const void * pData)
{
	StagingBuffer stagingBuffer(device, memoryProperties, pData);
	DeviceLocalBuffer deviceLocalBuffer(device, memoryProperties, size, usage);
	CommandBuffer commandBuffer(device, commandPool.getHandle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY);

	return deviceLocalBuffer;
}
