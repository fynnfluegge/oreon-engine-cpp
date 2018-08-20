#pragma once

#include "physicalDevice.h"
#include "logicalDevice.h"

class DeviceBundle {

public:
	DeviceBundle(PhysicalDevice physicalDevice, LogicalDevice logicalDevice);
	PhysicalDevice getPhysicalDevice() const;
	LogicalDevice getLogicalDevice() const;

private:
	PhysicalDevice physicalDevice;
	LogicalDevice logicalDevice;
};