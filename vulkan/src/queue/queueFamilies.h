#pragma once

#include <vector>
#include <vulkan\vulkan.h>

struct QueueFamily {
	int index;
	int count;
	int flags;
	int presentFlag;
};

class QueueFamilies {

public:
	QueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	std::vector<QueueFamily> getQueueFamilies() const;
private:
	std::vector<QueueFamily> queueFamilies;
};
