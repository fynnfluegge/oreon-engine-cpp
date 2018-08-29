#include "Image.h"
#include "util.h"

using namespace vk;

Image::Image(VkDevice device, uint32_t width, uint32_t height, uint32_t depth,
	VkFormat format, VkImageUsageFlags usage, uint32_t samples, uint32_t mipLevels) :
		device(device)
{
	VkExtent3D extent = {};
	extent.width = width;
	extent.height = height;
	extent.depth = depth;

	VkImageCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.extent = extent;
	createInfo.mipLevels = mipLevels;
	createInfo.arrayLayers = 1;
	createInfo.format = format;
	createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	createInfo.usage = usage;
	createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.samples = getSampleCountBit(samples);
	createInfo.flags = 0;

	vkCreateImage(device, &createInfo, nullptr, &handle);
}

void Image::allocate(VkPhysicalDeviceMemoryProperties memoryProperties, VkMemoryPropertyFlags memoryPropertyFlags)
{
	VkMemoryRequirements memoryRequirements;
	vkGetImageMemoryRequirements(device, handle, &memoryRequirements);

	VkMemoryAllocateInfo memAlloc = {};
	memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAlloc.allocationSize = memoryRequirements.size;
	memAlloc.memoryTypeIndex = getMemoryTypeIndex(memoryProperties,
		memoryRequirements.memoryTypeBits, memoryPropertyFlags);

	evaluateVkResult(vkAllocateMemory(device, &memAlloc, nullptr, &memory),
		"Failed to allocate image memory");
}

void Image::bindImageMemory()
{
	evaluateVkResult(vkBindImageMemory(device, handle, memory, 0),
		"Failed to bind memory to vertex buffer");
}

void Image::mapMemory(stbi_uc* pixels, uint64_t size)
{
	void* pData;
	evaluateVkResult(vkMapMemory(device, memory, 0, size, 0, &pData),
		"Failed to map image memory");

	memcpy(pData, pixels, static_cast<size_t>(size));
	vkUnmapMemory(device, memory);
	stbi_image_free(pixels);
}

void Image::destroy()
{
	vkFreeMemory(device, memory, nullptr);
	vkDestroyImage(device, handle, nullptr);
}
