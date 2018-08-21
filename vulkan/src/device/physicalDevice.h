#pragma once

#include <iostream>
#include <vector>
#include <vulkan\vulkan.h>

struct DeviceSurfaceProperties {
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamily {
	int index;
	int count;
	int flags;
	int presentFlag;
};

class PhysicalDevice {

public:
	PhysicalDevice(const VkSurfaceKHR surface);

private:
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	DeviceSurfaceProperties deviceSurfaceProperties;
	std::vector<const char*> supportedExtensionNames;
	std::vector<QueueFamily> queueFamilies;
};
