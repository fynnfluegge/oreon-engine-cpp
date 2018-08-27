#pragma once

#include <vector>
#include <vulkan\vulkan.h>

namespace vk {

	class DescriptorPool {
	public:
		DescriptorPool(VkDevice device, int poolCount);
		void create();
		void addPool(VkDescriptorType descriptorType, uint32_t descriptorCount);
		void destroy();
	private:
		VkDescriptorPool handle;
		const VkDevice device;
		std::vector<VkDescriptorPoolSize> poolSizes;
		uint32_t maxSets;
	};
}
