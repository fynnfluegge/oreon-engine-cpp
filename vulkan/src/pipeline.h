#pragma once

#include "vulkan\vulkan.h"

namespace vk {

	class Pipeline {
	public:
		Pipeline(VkDevice device);
		void setLayout(const VkDescriptorSetLayout* pLayouts, const VkPushConstantRange* pPushConstantRanges);
	private:
		VkPipeline handle;
		VkPipelineLayout layout;
		const VkDevice device;

	};
}
