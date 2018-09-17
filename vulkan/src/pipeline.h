#pragma once

#include <vulkan\vulkan.h>
#include <vector>
#include "vertex_input.h"
#include "render_pass.h"
#include "shader_pipeline.h"

namespace vk {

	class Pipeline {
	public:
		Pipeline(VkDevice device);
		void createGraphicsPipeline(ShaderPipeline shaderPipeline, RenderPass renderPass);
		void createComputePipeline(ShaderModule shader);
		void setLayout(const VkDescriptorSetLayout* pLayouts, const VkPushConstantRange* pPushConstantRanges);
		void setVertexInput(const VertexInput& vertexInput);
		void setPushConstantsRange(VkShaderStageFlags stageFlags, uint32_t size);
		void setInputAssembly(VkPrimitiveTopology topology);
		void setViewportAndScissor(float width, float height);
		void setRasterizer();
		void setMultisamplingState(uint32_t samples);
		void addColorBlendAttachment();
		void addColorBlendAttachment(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor,
			VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp colorBlendOp, VkBlendOp alphaBlendOp);
		void setColorBlendState();
		void setDepthAndStencilState(VkBool32 depthTestEnable);
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
		VkPipelineMultisampleStateCreateInfo multisamplingState;
		VkPipelineColorBlendStateCreateInfo colorBlendingState;
		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachmentStates;
		VkPipelineDepthStencilStateCreateInfo depthStencilState;
		VkPipelineDynamicStateCreateInfo dynamicState;
		VkPipelineTessellationStateCreateInfo tessellationState;
		VkViewport viewport;
		VkRect2D scissor;
		std::vector<VkDynamicState> dynamicStates;
		std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
	};
}
