#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class DescriptorSet {
	public:
		DescriptorSet(VkDevice device, VkDescriptorPool descriptorPool,
			VkDescriptorSetLayout* descriptorSetLayouts);
		void updateDescriptorBuffer(VkBuffer buffer, uint64_t range, uint64_t offset,
			uint32_t binding, VkDescriptorType descriptorType);
		void updateDescriptorImageBuffer(VkImageView imageView, VkImageLayout imageLayout,
			VkSampler sampler, uint32_t binding, VkDescriptorType descriptorType);
		void destroy();
	private:
		VkDescriptorSet handle;
		const VkDevice device;
		const VkDescriptorPool descriptorPool;
	};
}
