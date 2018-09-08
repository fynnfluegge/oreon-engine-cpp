#pragma once

#include <vulkan\vulkan.h>
#include <vector>
#include "vertex_input.h"

namespace vk {

	class Pipeline {
	public:
		Pipeline(VkDevice device);
		//void createGraphicsPipeline(ShaderPipeline shaderPipeline, long renderPass);
		void setLayout(const VkDescriptorSetLayout* pLayouts, const VkPushConstantRange* pPushConstantRanges);
		void setVertexInput(const VertexInput& vertexInput);
		void setPushConstantsRange(VkShaderStageFlags stageFlags, uint32_t size);
		void setInputAssembly(VkPrimitiveTopology topology);
		void setViewportAndScissor(float width, float height);
		void setRasterizer();
		void setMultisampling(uint32_t samples);
		void addColorBlendAttachment();
		void addColorBlendAttachment(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor,
			VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp colorBlendOp, VkBlendOp alphaBlendOp);
		void setColorBlendState();
		void setDepthAndStencilTest(VkBool32 depthTestEnable);
		void setDynamicState();
		void setTessellationState(uint32_t patchControlPoints);
		void destroy();
	private:
		VkPipeline handle;
		VkPipelineLayout layout;
		const VkDevice device;
		VkPipelineVertexInputStateCreateInfo vertexInputState;
		VkPipelineInputAssemblyStateCreateInfo inputAssembly;
		VkPushConstantRange pushConstantRange;
		VkPipelineViewportStateCreateInfo viewportAndScissorState;
		VkPipelineRasterizationStateCreateInfo rasterizer;
		VkPipelineMultisampleStateCreateInfo multisampling;
		VkPipelineColorBlendStateCreateInfo colorBlending;
		std::vector<VkPipelineColorBlendAttachmentState> colorBlendStates;
		VkPipelineDepthStencilStateCreateInfo depthStencil;
		VkPipelineDynamicStateCreateInfo dynamicState;
		VkPipelineTessellationStateCreateInfo tessellationInfo;
		VkViewport viewport;
		VkRect2D scissor;
		std::vector<VkDynamicState> dynamicStates;
		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
	};
}
