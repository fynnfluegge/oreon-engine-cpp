#include "descriptor_pool.h"

using namespace vk;

DescriptorPool::DescriptorPool(VkDevice device, int poolCount) : device(device), maxSets(0),
	poolSizes(std::vector<VkDescriptorPoolSize>(poolCount))
{
}

void DescriptorPool::create()
{
	VkDescriptorPoolCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	createInfo.pPoolSizes = poolSizes.data();
	createInfo.maxSets = maxSets;
	createInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
}

void DescriptorPool::addPool(VkDescriptorType descriptorType, uint32_t descriptorCount)
{
	VkDescriptorPoolSize poolSize = {};
	poolSize.type = descriptorType;
	poolSize.descriptorCount = descriptorCount;

	poolSizes.push_back(poolSize);
	maxSets += descriptorCount;
}

void DescriptorPool::destroy()
{
	vkDestroyDescriptorPool(device, handle, nullptr);
}
