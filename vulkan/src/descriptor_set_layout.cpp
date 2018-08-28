#include "descriptor_set_layout.h"
#include "util.h"

using namespace vk;

DescriptorSetLayout::DescriptorSetLayout(VkDevice device, int bindingCount) :
	device(device), layoutBindings(std::vector<VkDescriptorSetLayoutBinding>(bindingCount))
{
}

void DescriptorSetLayout::create()
{
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.pBindings = layoutBindings.data();
	layoutInfo.flags = 0;

	evaluateVkResult(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &handle),
		"Failed to create DescriptorSetLayout");
}

void DescriptorSetLayout::addLayoutBinding(uint32_t binding, VkDescriptorType type,
	VkShaderStageFlags stageflags)
{
	VkDescriptorSetLayoutBinding layoutBinding = {};
	layoutBinding.binding = binding;
	layoutBinding.descriptorType = type;
	layoutBinding.descriptorCount = 1;
	layoutBinding.stageFlags = stageflags;
	layoutBinding.pImmutableSamplers = nullptr;
}

void DescriptorSetLayout::destroy()
{
	vkDestroyDescriptorSetLayout(device, handle, nullptr);
}
