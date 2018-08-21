#pragma once

class LogicalDevice {

public:
	LogicalDevice(PhysicalDevice physicalDevice);

private:
	VkDevice handle;

};
