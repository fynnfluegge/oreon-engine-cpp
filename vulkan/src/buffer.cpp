#include "buffer.h"
#include "util\util.h"

using namespace vk;

Buffer::Buffer(VkDevice device, uint64_t size, VkBufferUsageFlags usage) :
	device(device), size(size)
{
	VkBufferCreateInfo bufInfo = {};
	bufInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufInfo.size = size;
	bufInfo.usage = usage;
	bufInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	bufInfo.flags = 0;

	evaluateVkResult(vkCreateBuffer(device, &bufInfo, nullptr, &handle),
		"Failed to create buffer");
}

void Buffer::allocate(VkPhysicalDeviceMemoryProperties memoryProperties, VkMemoryPropertyFlags memoryPropertyFlags)
{
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(device, handle, &memoryRequirements);

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAlloc.allocationSize = memoryRequirements.size;
	memAlloc.memoryTypeIndex = getMemoryTypeIndex(memoryProperties,
		memoryRequirements.memoryTypeBits, memoryPropertyFlags);

	evaluateVkResult(vkAllocateMemory(device, &memAlloc, nullptr, &memory),
		"Failed to allocate vertex memory");
}

void Buffer::bindBufferMemory()
{
	evaluateVkResult(vkBindBufferMemory(device, handle, memory, 0),
		"Failed to map image memory");
}

void Buffer::mapMemory(const void* pData)
{
	void* pMemoryData;
	evaluateVkResult(vkMapMemory(device, memory, 0, size, 0, &pMemoryData),
		"Failed to map image memory");

	memcpy(pMemoryData, pData, static_cast<size_t>(size));
	vkUnmapMemory(device, memory);
}

void Buffer::destroy()
{
	vkFreeMemory(device, memory, nullptr);
	vkDestroyBuffer(device, handle, nullptr);
}
