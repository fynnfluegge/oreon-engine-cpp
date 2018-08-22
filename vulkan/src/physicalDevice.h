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
	uint32_t count;
	uint32_t flags;
	VkBool32 presentFlag;
	QueueFamily() : index(-1) {};
};

class PhysicalDevice {

public:
	PhysicalDevice(const VkSurfaceKHR surface);
	const VkPhysicalDevice& getHandle();
	const VkPhysicalDeviceProperties& getProperties();
	const QueueFamily getGraphicsQueueFamily();
	const QueueFamily getComputeQueueFamily();
	const QueueFamily getTransferQueueFamily();
	const QueueFamily getSparseBindingQueueFamily();
	const QueueFamily getPresentationQueueFamily();
	const QueueFamily getGraphicsAndPresentationQueueFamily();
	const QueueFamily getComputeExclusiveQueueFamily();
	const QueueFamily getTransferExclusiveQueueFamily();

private:
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	DeviceSurfaceProperties deviceSurfaceProperties;
	std::vector<const char*> supportedExtensionNames;
	std::vector<QueueFamily> queueFamilies;
};
