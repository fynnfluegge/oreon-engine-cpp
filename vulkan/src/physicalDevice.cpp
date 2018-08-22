#include "physicalDevice.h"
#include "vk_context.h"
#include "util.h"

using namespace vk;

PhysicalDevice::PhysicalDevice(const VkSurfaceKHR surface)
{
	uint32_t deviceCount = 0;
	VkResult vkResult = vkEnumeratePhysicalDevices(Context::getInstance().getVkInstance(), &deviceCount, nullptr);
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get number of physical devices: " << translateVkResult(vkResult) << std::endl;
	}

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::cout << "Available Physical Devices: " << deviceCount << std::endl;

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkResult = vkEnumeratePhysicalDevices(Context::getInstance().getVkInstance(), &deviceCount, devices.data());
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get physical devices: " << translateVkResult(vkResult) << std::endl;
	}

	handle = devices.at(0);

	vkGetPhysicalDeviceProperties(handle, &properties);

	std::cout << "Device: " << properties.deviceName << std::endl;

	vkGetPhysicalDeviceFeatures(handle, &features);
	vkGetPhysicalDeviceMemoryProperties(handle, &memoryProperties);

	uint32_t extensionCount;
	vkResult = vkEnumerateDeviceExtensionProperties(handle, nullptr, &extensionCount, nullptr);
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get number of supported device extensions: " << translateVkResult(vkResult) << std::endl;
	}
	supportedExtensions.resize(extensionCount);
	vkResult = vkEnumerateDeviceExtensionProperties(handle, nullptr, &extensionCount, supportedExtensions.data());
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get supported device extensions: " << translateVkResult(vkResult) << std::endl;
	}

	vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(handle, surface, &deviceSurfaceProperties.surfaceCapabilities);
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get physical device surface capabilities: " << translateVkResult(vkResult) << std::endl;
	}

	uint32_t formatCount;
	vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, nullptr);
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to query number of physical device surface formats: " << vk::translateVkResult(vkResult) << std::endl;
	}

	if (formatCount != 0) {
		deviceSurfaceProperties.formats.resize(formatCount);
		vkResult = vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, deviceSurfaceProperties.formats.data());
		if (vkResult != VK_SUCCESS) {
			std::cout << "Failed to query physical device surface formats: " << translateVkResult(vkResult) << std::endl;
		}
	}

	uint32_t presentModeCount;
	vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, nullptr);
	if (vkResult != VK_SUCCESS) {
		std::cout << "Failed to get number of physical device surface presentation modes: " << translateVkResult(vkResult) << std::endl;
	}

	if (presentModeCount != 0) {
		deviceSurfaceProperties.presentModes.resize(presentModeCount);
		vkResult = vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, deviceSurfaceProperties.presentModes.data());
		if (vkResult != VK_SUCCESS) {
			std::cout << "Failed to get physical device surface presentation modes: " << translateVkResult(vkResult) << std::endl;
		}
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
			vkResult = vkGetPhysicalDeviceSurfaceSupportKHR(handle, i, surface, &supportPresent);
			if (vkResult != VK_SUCCESS) {
				std::cout << "Failed to query physical device surface support: " << translateVkResult(vkResult) << std::endl;
			}

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

bool PhysicalDevice::deviceExtensionSupported(const char* extension)
{
	for (VkExtensionProperties supportedExtension : supportedExtensions) {
		if (strcmp(supportedExtension.extensionName, extension) == 0) {
			return true;
		}
	}
	return false;
}

const VkPhysicalDevice& PhysicalDevice::getHandle()
{
	return handle;
}

const VkPhysicalDeviceProperties& PhysicalDevice::getProperties()
{
	return properties;
}

