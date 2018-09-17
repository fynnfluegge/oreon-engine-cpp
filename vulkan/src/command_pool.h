#pragma once

#include <iostream>
#include <vulkan\vulkan.h>

namespace vk {

	class CommandPool {
	public:
		CommandPool(VkDevice device, uint32_t queueFamilyIndex);
		void destroy();
		VkCommandPool getHandle() const;
	private:
		VkCommandPool handle;
		const VkDevice device;
	};
}
