#include "fence.h"
#include "util\util.h"

using namespace vk;

Fence::Fence(VkDevice device) : device(device)
{
	VkFenceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	evaluateVkResult(vkCreateFence(device, &createInfo, nullptr, &handle), "Failed to create fence");
}

void Fence::reset()
{
	evaluateVkResult(vkResetFences(device, 1, &handle), "Failed to reset fence");
}

void Fence::wait()
{
	evaluateVkResult(vkWaitForFences(device, 1, &handle, true, 1000000000l), "Failed to wait for Fence");
}

void Fence::destroy()
{
	vkDestroyFence(device, handle, nullptr);
}

VkFence Fence::getHandle()
{
	return handle;
}
