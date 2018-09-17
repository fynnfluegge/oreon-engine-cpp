#include "physicalDevice.h"
#include "vk_context.h"
#include "util\util.h"

using namespace vk;

PhysicalDevice::PhysicalDevice(const VkSurfaceKHR surface)
{
	uint32_t deviceCount = 0;
	evaluateVkResult(vkEnumeratePhysicalDevices(Context::getInstance().getVkInstance(), &deviceCount, nullptr),
		"Failed to get number of physical devices");

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::cout << "Available Physical Devices: " << deviceCount << std::endl;

	std::vector<VkPhysicalDevice> devices(deviceCount);
	evaluateVkResult(vkEnumeratePhysicalDevices(Context::getInstance().getVkInstance(), &deviceCount, devices.data()),
		"Failed to get physical devices");

	handle = devices.at(0);

	vkGetPhysicalDeviceProperties(handle, &properties);

	std::cout << "Device: " << properties.deviceName << std::endl;

	vkGetPhysicalDeviceFeatures(handle, &features);
	vkGetPhysicalDeviceMemoryProperties(handle, &memoryProperties);

	uint32_t extensionCount;
	evaluateVkResult(vkEnumerateDeviceExtensionProperties(handle, nullptr, &extensionCount, nullptr),
		"Failed to get number of supported device extensions");

	supportedExtensions.resize(extensionCount);
	evaluateVkResult(vkEnumerateDeviceExtensionProperties(handle, nullptr, &extensionCount, supportedExtensions.data()),
		"Failed to get supported device extensions");

	evaluateVkResult(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(handle, surface, &deviceSurfaceProperties.surfaceCapabilities),
		"Failed to get physical device surface capabilities");

	uint32_t formatCount;
	evaluateVkResult(vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, nullptr),
		"Failed to query number of physical device surface formats");

	if (formatCount != 0) {
		deviceSurfaceProperties.formats.resize(formatCount);
		vk::evaluateVkResult(vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, deviceSurfaceProperties.formats.data()),
			"Failed to query physical device surface formats");
	}

	uint32_t presentModeCount;
	evaluateVkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, nullptr),
		"Failed to get number of physical device surface presentation modes");

	if (presentModeCount != 0) {
		deviceSurfaceProperties.presentModes.resize(presentModeCount);
		evaluateVkResult(vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, deviceSurfaceProperties.presentModes.data()),
			"Failed to get physical device surface presentation modes");
	}

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, queueFamilyProperties.data());

	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		QueueFamily queueFamily;
		queueFamily.index = i;
		queueFamily.count = queueFamilyProperties.at(i).queueCount;
		queueFamily.flags = queueFamilyProperties.at(i).queueFlags;
		queueFamily.presentFlag = false;

		if (surface != nullptr) {
			VkBool32 supportPresent;
			evaluateVkResult(vkGetPhysicalDeviceSurfaceSupportKHR(handle, i, surface, &supportPresent),
				"Failed to query physical device surface support");

			if (supportPresent) {
				queueFamily.presentFlag = true;
			}
		}

		queueFamilies.push_back(queueFamily);
	}

}

const QueueFamily PhysicalDevice::getGraphicsQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags & VK_QUEUE_GRAPHICS_BIT) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

const QueueFamily PhysicalDevice::getComputeQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags & VK_QUEUE_COMPUTE_BIT) {
			return queueFamily;
		}
	}

	return QueueFamily();
}

const QueueFamily PhysicalDevice::getTransferQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags & VK_QUEUE_TRANSFER_BIT) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

const QueueFamily PhysicalDevice::getSparseBindingQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags & VK_QUEUE_SPARSE_BINDING_BIT) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

const QueueFamily PhysicalDevice::getPresentationQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags == VK_TRUE) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

const QueueFamily PhysicalDevice::getGraphicsAndPresentationQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {

		if (queueFamily.flags & VK_QUEUE_GRAPHICS_BIT
			&& queueFamily.presentFlag == VK_TRUE) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

const QueueFamily PhysicalDevice::getComputeExclusiveQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags == VK_QUEUE_COMPUTE_BIT) {
			return queueFamily;
		}
	}

	return QueueFamily();
}

const QueueFamily PhysicalDevice::getTransferExclusiveQueueFamily()
{
	for (QueueFamily queueFamily : queueFamilies) {
		if (queueFamily.flags == VK_QUEUE_TRANSFER_BIT) {
			return queueFamily;
		}
	}
	return QueueFamily();
}

bool PhysicalDevice::isExtensionSupported(const char* extension)
{
	for (VkExtensionProperties supportedExtension : supportedExtensions) {
		if (strcmp(supportedExtension.extensionName, extension) == 0) {
			return true;
		}
	}
	return false;
}

bool PhysicalDevice::checkDeviceFormatAndColorSpaceSupport(VkFormat format, VkColorSpaceKHR colorSpace) const
{
	if (deviceSurfaceProperties.formats.at(0).format == VK_FORMAT_UNDEFINED) {
		// surface has no format restrictions
		return true;
	}

	for (const auto& surfaceFormat : deviceSurfaceProperties.formats) {

		if (surfaceFormat.format == format
			&& surfaceFormat.colorSpace == colorSpace) {
			return true;
		}
	}
	return false;
}

bool PhysicalDevice::checkDevicePresentationModeSupport(VkPresentModeKHR presentMode) const
{
	for (const auto& availablePresentMode : deviceSurfaceProperties.presentModes) {

		if (availablePresentMode == presentMode) {
			return true;
		}
	}
	return false;
}

uint32_t PhysicalDevice::getMinImageCount4TripleBuffering() const
{
	int minImageCount = deviceSurfaceProperties.surfaceCapabilities.minImageCount + 1;
	if ((deviceSurfaceProperties.surfaceCapabilities.maxImageCount > 0) &&
			(minImageCount > deviceSurfaceProperties.surfaceCapabilities.maxImageCount)) {
		minImageCount = deviceSurfaceProperties.surfaceCapabilities.maxImageCount;
	}

	return minImageCount;
}

DeviceSurfaceProperties PhysicalDevice::getDeviceSurfaceProperties() const
{
	return deviceSurfaceProperties;
}

const VkPhysicalDevice& PhysicalDevice::getHandle()
{
	return handle;
}

const VkPhysicalDeviceProperties& PhysicalDevice::getProperties()
{
	return properties;
}

