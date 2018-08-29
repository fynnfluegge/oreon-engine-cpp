#include "pipeline.h"

using namespace vk;

Pipeline::Pipeline(VkDevice device) : device(device)
{
}

void Pipeline::setLayout(const VkDescriptorSetLayout* pLayouts, const VkPushConstantRange* pPushConstantRanges)
{
	VkPipelineLayoutCreateInfo pipelineLayout = {};
	pipelineLayout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayout.pSetLayouts = pLayouts;
	pipelineLayout.pPushConstantRanges = pPushConstantRanges;
}
