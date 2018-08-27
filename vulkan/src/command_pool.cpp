#include "command_pool.h"
#include "util.h"

vk::CommandPool::CommandPool(VkDevice device, uint32_t queueFamilyIndex) : device(device)
{
	VkCommandPoolCreateInfo cmdPoolCreateInfo = {};
	cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	cmdPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
	cmdPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	VkResult vkResult = vkCreateCommandPool(device, &cmdPoolCreateInfo, nullptr, &handle);

	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to create command pool: "
			<< translateVkResult(vkResult) << std::endl;
	}
}

void vk::CommandPool::destroy()
{
	vkDestroyCommandPool(device, handle, nullptr);
}
