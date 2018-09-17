#include "descriptor_set.h"
#include "util\util.h"

using namespace vk;

DescriptorSet::DescriptorSet(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorSetLayout* descriptorSetLayouts)
	: device(device), descriptorPool(descriptorPool)
{
	VkDescriptorSetAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocateInfo.descriptorPool = descriptorPool;
	allocateInfo.pSetLayouts = descriptorSetLayouts;

	evaluateVkResult(vkAllocateDescriptorSets(device, &allocateInfo, &handle),
		"Failed to create Descriptor Set");
}

void DescriptorSet::updateDescriptorBuffer(VkBuffer buffer, uint64_t range, uint64_t offset,
	uint32_t binding, VkDescriptorType descriptorType)
{
	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = buffer;
	bufferInfo.offset = offset;
	bufferInfo.range = range;

	VkWriteDescriptorSet writeDescriptor = {};
	writeDescriptor.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptor.dstSet = handle;
	writeDescriptor.dstBinding = binding;
	writeDescriptor.dstArrayElement = 0;
	writeDescriptor.descriptorType = descriptorType;
	writeDescriptor.pBufferInfo = &bufferInfo;

	vkUpdateDescriptorSets(device, 1, &writeDescriptor, 0, nullptr);
}

void DescriptorSet::updateDescriptorImageBuffer(VkImageView imageView, VkImageLayout imageLayout,
	VkSampler sampler, uint32_t binding, VkDescriptorType descriptorType)
{
	VkDescriptorImageInfo imageInfo = {};
	imageInfo.imageLayout = imageLayout;
	imageInfo.imageView = imageView;
	imageInfo.sampler = sampler;

	VkWriteDescriptorSet writeDescriptor = {};
	writeDescriptor.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptor.dstSet = handle;
	writeDescriptor.dstBinding = binding;
	writeDescriptor.dstArrayElement = 0;
	writeDescriptor.descriptorType = descriptorType;
	writeDescriptor.pImageInfo = &imageInfo;

	vkUpdateDescriptorSets(device, 1, &writeDescriptor, 0, nullptr);
}

void DescriptorSet::destroy()
{
	vkFreeDescriptorSets(device, descriptorPool, 1, &handle);
}
