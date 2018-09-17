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
	uint32_t index;
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
	bool isExtensionSupported(const char* extension);
	bool checkDeviceFormatAndColorSpaceSupport(VkFormat format, VkColorSpaceKHR colorSpace) const;
	bool checkDevicePresentationModeSupport(VkPresentModeKHR presentMode) const;
	uint32_t getMinImageCount4TripleBuffering() const;
	DeviceSurfaceProperties getDeviceSurfaceProperties() const;
private:
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	DeviceSurfaceProperties deviceSurfaceProperties;
	std::vector<VkExtensionProperties> supportedExtensions;
	std::vector<QueueFamily> queueFamilies;
};
