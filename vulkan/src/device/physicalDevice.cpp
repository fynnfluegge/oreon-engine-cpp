#include "physicalDevice.h"
#include "context\VkContext.h"
#include "util\util.h"

PhysicalDevice::PhysicalDevice(const VkSurfaceKHR surface)
{
	uint32_t deviceCount = 0;
	VkResult vkResult = vkEnumeratePhysicalDevices(VkContext::getInstance().getVkInstance(), &deviceCount, nullptr);

	if (vkResult == VK_SUCCESS) {
		std::cout << "Failed to get number of physical devices: " << vk::translateVkResult(vkResult) << std::endl;
	}

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::cout << "Available Physical Devices: " << deviceCount << std::endl;

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkResult = vkEnumeratePhysicalDevices(VkContext::getInstance().getVkInstance(), &deviceCount, devices.data());

	handle = devices.at(0);

	vkGetPhysicalDeviceProperties(handle, &properties);

	std::cout << "Device: " << properties.deviceName << std::endl;

	vkGetPhysicalDeviceFeatures(handle, &features);
	vkGetPhysicalDeviceMemoryProperties(handle, &memoryProperties);

	vkResult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(handle, surface, &deviceSurfaceProperties.surfaceCapabilities);
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		deviceSurfaceProperties.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(handle, surface, &formatCount, deviceSurfaceProperties.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		deviceSurfaceProperties.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(handle, surface, &presentModeCount, deviceSurfaceProperties.presentModes.data());
	}

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(handle, &queueFamilyCount, queueFamilyProperties.data());

	for (unsigned int i = 0; i < queueFamilyCount; i++) {
		std::cout << queueFamilyProperties.at(i).queueFlags << std::endl;
	}

}
