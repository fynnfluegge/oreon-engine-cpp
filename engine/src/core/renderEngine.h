#pragma once

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include "context/vkContext.h"
#include "context/engineContext.h"
#include "device\physicalDevice.h"

class RenderEngine {

public:
	void init();
	void update();
	void render();
	void shutdown();
private:
	VkSurfaceKHR surface;
};
