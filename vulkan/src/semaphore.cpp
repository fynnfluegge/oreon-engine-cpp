#include "semaphore.h"
#include "util\util.h"

using namespace vk;

Semaphore::Semaphore(VkDevice device) : device(device)
{
	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.flags = 0;

	evaluateVkResult(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &handle),
		"Failed to create semaphore");
}

void Semaphore::destroy()
{
	vkDestroySemaphore(device, handle, nullptr);
}
