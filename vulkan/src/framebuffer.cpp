#include "framebuffer.h"
#include "util\util.h"

using namespace vk;

Framebuffer::Framebuffer(VkDevice device, uint32_t width, uint32_t height, uint32_t layers,
	const VkImageView* pAttachments, VkRenderPass renderPass) : device(device)
{
	VkFramebufferCreateInfo framebufferInfo = {};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.pAttachments = pAttachments;
	framebufferInfo.flags = 0;
	framebufferInfo.height = height;
	framebufferInfo.width = width;
	framebufferInfo.layers = layers;
	framebufferInfo.renderPass = renderPass;

	evaluateVkResult(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &handle),
		"Failed to create framebuffer");
}

void Framebuffer::destroy()
{
	vkDestroyFramebuffer(device, handle, nullptr);
}
