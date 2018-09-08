#include "pipeline.h"
#include "util.h"

using namespace vk;

Pipeline::Pipeline(VkDevice device) : device(device)
{
}

void Pipeline::setLayout(const VkDescriptorSetLayout* pLayouts, const VkPushConstantRange* pPushConstantRanges)
{
	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
	pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreateInfo.pSetLayouts = pLayouts;
	pipelineLayoutCreateInfo.pPushConstantRanges = pPushConstantRanges;

	evaluateVkResult(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &layout),
		"Failed to create pipeline layout");
}

void Pipeline::setVertexInput(const VertexInput& vertexInput)
{
	vertexInputState = {};
	vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputState.pVertexBindingDescriptions = &vertexInput.getBindingDescription();
	vertexInputState.pVertexAttributeDescriptions = vertexInput.getAttributeDescriptions().data();
}

void Pipeline::setPushConstantsRange(VkShaderStageFlags stageFlags, uint32_t size)
{
	pushConstantRange = {};
	pushConstantRange.stageFlags = stageFlags;
	pushConstantRange.size = size;
	pushConstantRange.offset = 0;
}

void Pipeline::setInputAssembly(VkPrimitiveTopology topology)
{
	inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = topology;
	inputAssembly.primitiveRestartEnable = VK_FALSE;
}

void Pipeline::setViewportAndScissor(float width, float height)
{
	viewport = {};
	viewport.x = 0;
	viewport.y = 0;
	viewport.width = width;
	viewport.height = height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor = {};
	scissor.extent.width = width;
	scissor.extent.height = height;
	scissor.offset.x = 0;
	scissor.offset.y = 0;

	VkPipelineViewportStateCreateInfo viewportAndScissorState = {};
	viewportAndScissorState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportAndScissorState.viewportCount = 1;
	viewportAndScissorState.pViewports = &viewport;
	viewportAndScissorState.scissorCount = 1;
	viewportAndScissorState.pScissors = &scissor;
}

void Pipeline::setRasterizer()
{
	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.cullMode = VK_CULL_MODE_NONE;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.lineWidth = 1.0f;
	rasterizer.depthClampEnable = false;
	rasterizer.depthBiasEnable = false;
	rasterizer.depthBiasConstantFactor = 0;
	rasterizer.depthBiasSlopeFactor = 0;
	rasterizer.depthBiasClamp = 0;
}

void Pipeline::setMultisampling(uint32_t samples)
{
	multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = getSampleCountBit(samples);
	multisampling.pSampleMask = nullptr;
	multisampling.minSampleShading = 1;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable = VK_FALSE;
}

void Pipeline::addColorBlendAttachment()
{
	VkPipelineColorBlendAttachmentState colorWriteMask = {};
	colorWriteMask.blendEnable = VK_FALSE;
	colorWriteMask.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
			| VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	colorBlendAttachments.push_back(colorWriteMask);
}

void Pipeline::addColorBlendAttachment(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor,
	VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp colorBlendOp, VkBlendOp alphaBlendOp)
{
	VkPipelineColorBlendAttachmentState colorWriteMask = {};
	colorWriteMask.blendEnable = VK_TRUE;
	colorWriteMask.srcColorBlendFactor = srcColorBlendFactor;
	colorWriteMask.dstColorBlendFactor = dstColorBlendFactor;
	colorWriteMask.colorBlendOp = colorBlendOp;
	colorWriteMask.srcAlphaBlendFactor = srcAlphaBlendFactor;
	colorWriteMask.dstAlphaBlendFactor = dstAlphaBlendFactor;
	colorWriteMask.alphaBlendOp = alphaBlendOp;
	colorWriteMask.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT
			| VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	colorBlendAttachments.push_back(colorWriteMask);
}

void Pipeline::setColorBlendState()
{
	colorBlendStates = std::vector< VkPipelineColorBlendAttachmentState>(colorBlendAttachments.size());

	colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.pAttachments = colorBlendStates.data();
}

void Pipeline::setDepthAndStencilTest(VkBool32 depthTestEnable)
{
	depthStencil = {};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable= depthTestEnable;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.back.failOp = VK_STENCIL_OP_KEEP;
	depthStencil.back.passOp = VK_STENCIL_OP_KEEP;
	depthStencil.back.compareOp = VK_COMPARE_OP_ALWAYS;
	depthStencil.front = depthStencil.back;
}

void Pipeline::setDynamicState()
{
	dynamicStates = std::vector<VkDynamicState>(2);
	dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);

	dynamicState = {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.pDynamicStates = dynamicStates.data();
}

void Pipeline::setTessellationState(uint32_t patchControlPoints)
{
	tessellationInfo = {};
	tessellationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	tessellationInfo.flags = 0;
	tessellationInfo.patchControlPoints = patchControlPoints;
}

void Pipeline::destroy()
{
	vkDestroyPipelineLayout(device, layout, nullptr);
	vkDestroyPipeline(device, handle, nullptr);
}
