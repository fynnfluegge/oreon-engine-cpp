#include "swapchain.h"
#include "util\util.h"

using namespace vk;

SwapChain::SwapChain(const LogicalDevice& logicalDevice, const PhysicalDevice& physicalDevice, 
	VkSurfaceKHR surface, VkImageView imageView, uint32_t width, uint32_t height)
		: device(logicalDevice.getHandle()), fence_drawCompleted(logicalDevice.getHandle())
{
	extent = physicalDevice.getDeviceSurfaceProperties().surfaceCapabilities.currentExtent;
	extent.width = width;
	extent.height = height;

	VkFormat imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
	VkColorSpaceKHR colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAILBOX_KHR;

	if (!physicalDevice.checkDeviceFormatAndColorSpaceSupport(imageFormat, colorSpace)) {
		std::cerr << "Desired format and colorspace not supported" << std::endl;
	}

	if (!physicalDevice.checkDevicePresentationModeSupport(presentMode)) {

		if (physicalDevice.checkDevicePresentationModeSupport(VK_PRESENT_MODE_FIFO_KHR))
			presentMode = VK_PRESENT_MODE_FIFO_KHR;
		else
			presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
	}

	uint32_t minImageCount = physicalDevice.getMinImageCount4TripleBuffering();

	VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	swapchainCreateInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	swapchainCreateInfo.minImageCount = minImageCount;
	swapchainCreateInfo.imageFormat = imageFormat;
	swapchainCreateInfo.imageColorSpace = colorSpace;
	swapchainCreateInfo.imageExtent = extent;
	swapchainCreateInfo.presentMode = presentMode;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.clipped = VK_FALSE;
		// presentation queue family and graphics queue family are the same
	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.pQueueFamilyIndices = VK_NULL_HANDLE;

	evaluateVkResult(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &handle),
		"Failed to create swapchain");
}
