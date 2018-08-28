#pragma once

#include <vector>
#include <vulkan\vulkan.h>

namespace vk {

	class DescriptorSetLayout {
	public:
		DescriptorSetLayout(VkDevice device, int bindingCount);
		void create();
		void addLayoutBinding(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageflags);
		void destroy();
	private:
		VkDescriptorSetLayout handle;
		const VkDevice device;
		std::vector<VkDescriptorSetLayoutBinding> layoutBindings;
	};
}
