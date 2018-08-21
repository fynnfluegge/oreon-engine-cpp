#pragma once

#include <iostream>
#include <vector>
#include <vulkan\vulkan.h>
#include "deviceSurfaceCapabilities.h"

class PhysicalDevice {

public:
	PhysicalDevice(const VkSurfaceKHR surface);

private:
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	DeviceSurfaceCapabilities surfaceCapabilities;
	std::vector<const char*> supportedExtensionNames;
};
