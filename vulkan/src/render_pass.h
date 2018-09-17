#pragma once

#include <vulkan\vulkan.h>
#include <vector>

namespace vk {
	class RenderPass {
	public:
		RenderPass(VkDevice device);
		void createRenderPass();
		void createSubpass();
		void addColorAttachment(uint32_t location, VkImageLayout layout,
			VkFormat format, uint32_t samples,
			VkImageLayout initialLayout, VkImageLayout finalLayout);
		void addDepthAttachment(uint32_t location, VkImageLayout layout,
			VkFormat format, uint32_t samples,
			VkImageLayout initialLayout, VkImageLayout finalLayout);
		void addSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
			VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
			VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask,
			VkDependencyFlags dependencyFlags);
		void destroy();
		VkRenderPass getHandle() const;
	private:
		VkRenderPass handle;
		std::vector<VkAttachmentReference> colorAttachmentReferences;
		VkAttachmentReference depthAttachmentReference;
		std::vector<VkAttachmentDescription> attachmentDescriptions;
		std::vector<VkSubpassDescription> subpassDescriptions;
		std::vector<VkSubpassDependency> subpassDependendies;
		const VkDevice device;
		void addAttachmentDescription(VkFormat format, uint32_t samples,
			VkImageLayout initialLayout, VkImageLayout finalLayout);
	};
}