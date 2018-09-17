#pragma once

#include <vulkan\vulkan.h>
#include "logicalDevice.h"
#include "physicalDevice.h"
#include "fence.h"

namespace vk {
	
	class SwapChain {
	public:
		SwapChain(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice,
			VkSurfaceKHR surface, VkImageView imageView, uint32_t width, uint32_t height);
	private:
		VkSwapchainKHR handle;
		VkExtent2D extent;
		Fence fence_drawCompleted;
		const VkDevice device;
	};
}
