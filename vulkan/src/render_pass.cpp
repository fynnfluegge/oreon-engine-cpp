#include "render_pass.h"
#include "util\util.h"

using namespace vk;

RenderPass::RenderPass(VkDevice device) : device(device)
{
}

void RenderPass::createRenderPass()
{
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.pAttachments = attachmentDescriptions.data();
	renderPassCreateInfo.pSubpasses = subpassDescriptions.data();
	renderPassCreateInfo.pDependencies = subpassDependendies.data();

	evaluateVkResult(vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, &handle),
		"Failed to create render pass");
}

void RenderPass::createSubpass()
{
	// TODO memcpy inputAttachmentReferences, colorAttachmentReferences,
	//		depthStencilAttachmentReferences

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.pInputAttachments = nullptr;
	subpass.colorAttachmentCount = colorAttachmentReferences.size();
	subpass.pColorAttachments = colorAttachmentReferences.data();
	subpass.pResolveAttachments = nullptr;
	subpass.pDepthStencilAttachment = &depthAttachmentReference;
	subpass.pPreserveAttachments = nullptr;

	// TODO clear vectors

	subpassDescriptions.push_back(subpass);
}

void RenderPass::addColorAttachment(uint32_t location, VkImageLayout layout, VkFormat format,
	uint32_t samples, VkImageLayout initialLayout, VkImageLayout finalLayout)
{
	addAttachmentDescription(format, samples, initialLayout, finalLayout);

	VkAttachmentReference attachmentReference = {};
	attachmentReference.attachment = location;
	attachmentReference.layout = layout;

	colorAttachmentReferences.push_back(attachmentReference);
}

void RenderPass::addDepthAttachment(uint32_t location, VkImageLayout layout, VkFormat format,
	uint32_t samples, VkImageLayout initialLayout, VkImageLayout finalLayout)
{
	addAttachmentDescription(format, samples, initialLayout, finalLayout);

	depthAttachmentReference = {};
	depthAttachmentReference.attachment = location;
	depthAttachmentReference.layout = layout;
}

void RenderPass::addSubpassDependency(uint32_t srcSubpass, uint32_t dstSubpass,
	VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
	VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask,
	VkDependencyFlags dependencyFlags)
{
	VkSubpassDependency dependencies = {};
	dependencies.srcSubpass = srcSubpass;
	dependencies.dstSubpass = dstSubpass;
	dependencies.srcStageMask = srcStageMask;
	dependencies.dstStageMask = dstStageMask;
	dependencies.srcAccessMask = srcStageMask;
	dependencies.dstAccessMask = dstStageMask;
	dependencies.dependencyFlags = dependencyFlags;

	subpassDependendies.push_back(dependencies);
}

void RenderPass::destroy()
{
	vkDestroyRenderPass(device, handle, nullptr);
}

VkRenderPass RenderPass::getHandle() const
{
	return handle;
}

void RenderPass::addAttachmentDescription(VkFormat format, uint32_t samples,
	VkImageLayout initialLayout, VkImageLayout finalLayout)
{
	VkAttachmentDescription attachmentDescription = {};
	attachmentDescription.format = format;
	attachmentDescription.samples = getSampleCountBit(samples);
	attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachmentDescription.initialLayout = initialLayout;
	attachmentDescription.finalLayout = finalLayout;

	attachmentDescriptions.push_back(attachmentDescription);
}


