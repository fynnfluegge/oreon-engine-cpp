#pragma once

#include <thread>
#include "physicalDevice.h"

class LogicalDevice {

public:
	LogicalDevice(PhysicalDevice physicalDevice);
	VkQueue getDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);

private:
	VkDevice handle;
	int graphicsQueueFamilyIndex;
	int computeQueueFamilyIndex;
	int transferQueueFamilyIndex;
	//std::unordered_map<std::thread::id, DeviceBundle> devices;
	//std::unordered_map<std::thread::id, DeviceBundle> devices;
};
