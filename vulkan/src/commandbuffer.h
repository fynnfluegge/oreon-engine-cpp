#pragma once

#include <iostream>
#include <vulkan\vulkan.h>

namespace vk {

	class CommandBuffer {
	public:
		CommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel level);
		void beginRecord(VkCommandBufferUsageFlags usageFlags);
		void beginRecordSecondary(VkCommandBufferUsageFlags usageFlags,
			VkFramebuffer framebuffer, VkRenderPass renderPass, int subpass);
		void finishRecord();
		void beginRenderPassCmd(VkRenderPass renderPass, VkFramebuffer frameBuffer,
			uint32_t width, uint32_t height, int colorAttachmentCount, int depthAttachment,
			VkSubpassContents subpassContentsFlag);
		void beginRenderPassCmd(VkRenderPass renderPass, VkFramebuffer frameBuffer,
			uint32_t width, uint32_t height, int colorAattachmentCount, int depthAttachment,
			float clearR, float clearG, float clearB, float clearA, VkSubpassContents subpassContentsFlag);
		void endRenderPassCmd();
		void bindComputePipelineCmd(VkPipeline pipeline);
		void bindGraphicsPipelineCmd(VkPipeline pipeline);
		void pushConstantsCmd(VkPipelineLayout pipelineLayout, VkPipelineStageFlags stageFlags, const void* pData);
		void bindVertexInputCmd(VkBuffer vertexBuffer, VkBuffer indexBuffer);
		void bindVertexInputCmd(VkBuffer vertexBuffer);
		void bindComputeDescriptorSetsCmd(VkPipelineLayout pipelinyLayout, const VkDescriptorSet* pDescriptorSets);
		void bindGraphicsDescriptorSetsCmd(VkPipelineLayout pipelinyLayout, const VkDescriptorSet* pDescriptorSets);
		void clearColorImageCmd(VkImage image, VkImageLayout imageLayout);
		void drawIndexedCmd(uint32_t indexCount);
		void drawCmd(uint32_t vertexCount);
		void dispatchCmd(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ);
		void copyBufferCmd(VkBuffer srcBuffer, VkBuffer dstBuffer, uint64_t srcOffset, uint64_t dstOffset, uint64_t size);
		void copyBufferToImageCmd(VkBuffer srcBuffer, VkImage dstImage, uint32_t width, uint32_t height, uint32_t depth);
	private:
		VkCommandBuffer handle;
		void beginRenderPassCmd(VkRenderPass renderPass, VkFramebuffer frameBuffer,
			uint32_t width, uint32_t height, VkClearValue* clearValues, VkSubpassContents subpassContentsFlag);
		void bindDescriptorSetsCmd(VkPipelineLayout pipelinyLayout, const VkDescriptorSet* pDescriptorSets,
			VkPipelineBindPoint pipelineBindPoint);
	};
}
