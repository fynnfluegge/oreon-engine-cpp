#pragma once

#include "physicalDevice.h"

class LogicalDevice {

public:
	LogicalDevice(PhysicalDevice physicalDevice);

private:
	VkDevice handle;

};
