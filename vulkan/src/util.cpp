#include "util.h"

std::string vk::translateVkResult(VkResult vkResult) {
	switch (vkResult)
	{
	case VK_SUCCESS:
		return "Command successfully completed.";
	case VK_NOT_READY:
		return "A fence or query has not yet completed.";
	case VK_TIMEOUT:
		return "A wait operation has not completed in the specified time.";
	case VK_EVENT_SET:
		return "An event is signaled.";
	case VK_EVENT_RESET:
		return "An event is unsignaled.";
	case VK_INCOMPLETE:
		return "A return array was too small for the result.";
	case VK_SUBOPTIMAL_KHR:
		return "A swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.";

		// Error codes
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		return "A host memory allocation has failed.";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		return "A device memory allocation has failed.";
	case VK_ERROR_INITIALIZATION_FAILED:
		return "Initialization of an object could not be completed for implementation-specific reasons.";
	case VK_ERROR_DEVICE_LOST:
		return "The logical or physical device has been lost.";
	case VK_ERROR_MEMORY_MAP_FAILED:
		return "Mapping of a memory object has failed.";
	case VK_ERROR_LAYER_NOT_PRESENT:
		return "A requested layer is not present or could not be loaded.";
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		return "A requested extension is not supported.";
	case VK_ERROR_FEATURE_NOT_PRESENT:
		return "A requested feature is not supported.";
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible for implementation-specific reasons.";
	case VK_ERROR_TOO_MANY_OBJECTS:
		return "Too many objects of the type have already been created.";
	case VK_ERROR_FORMAT_NOT_SUPPORTED:
		return "A requested format is not supported on this device.";
	case VK_ERROR_SURFACE_LOST_KHR:
		return "A surface is no longer available.";
	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
		return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API.";
	case VK_ERROR_OUT_OF_DATE_KHR:
		return "A surface has changed in such a way that it is no longer compatible with the swapchain, and further presentation requests using the swapchain will fail. Applications must query the new surface properties and recreate their swapchain if they wish to continue presenting to the surface.";
	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
		return "The display used by a swapchain does not use the same presentable image layout, or is incompatible in a way that prevents sharing an image.";
	case VK_ERROR_VALIDATION_FAILED_EXT:
		return "A validation layer found an error.";
	default:
		return "VkResullt unknown";
	}
}

void vk::evaluateVkResult(VkResult vkResult, std::string error_message)
{
	if (vkResult != VK_SUCCESS) {
		std::cerr << error_message << ": " << translateVkResult(vkResult) << std::endl;
	}
}

VkSampleCountFlagBits vk::getSampleCountBit(uint32_t samples)
{
	VkSampleCountFlagBits sampleCountBit;

	switch (samples) {
		case 1: sampleCountBit = VK_SAMPLE_COUNT_1_BIT; break;
		case 2: sampleCountBit = VK_SAMPLE_COUNT_2_BIT; break;
		case 4: sampleCountBit = VK_SAMPLE_COUNT_4_BIT; break;
		case 8: sampleCountBit = VK_SAMPLE_COUNT_8_BIT; break;
		case 16: sampleCountBit = VK_SAMPLE_COUNT_16_BIT; break;
		case 32: sampleCountBit = VK_SAMPLE_COUNT_32_BIT; break;
		case 64: sampleCountBit = VK_SAMPLE_COUNT_64_BIT; break;
		default: std::cerr << "Multisamplecount: " << samples << ". Allowed numbers [1,2,4,8,16,32,64]" << std::endl;
	}

	return sampleCountBit;
}

uint32_t vk::getMemoryTypeIndex(VkPhysicalDeviceMemoryProperties memoryProperties,
	uint32_t memoryTypeBits, VkMemoryPropertyFlags properties)
{
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
		if ((memoryTypeBits & (1 << i)) != 0 &&
			(memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	std::cerr << "No memory Type found" << std::endl;

	return -1;
}
