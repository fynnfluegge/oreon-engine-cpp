#pragma once

#include <vector>
#include <vulkan\vulkan.h>
#include "queueFamily.h"

class QueueFamilies {

public:
	QueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	std::vector<QueueFamily> getQueueFamilies() const;
private:
	std::vector<QueueFamily> queueFamilies;
};
