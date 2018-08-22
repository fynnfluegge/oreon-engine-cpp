#pragma once

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include "vkContext.h"
#include "context/oeContext.h"

class RenderEngine {

public:
	void init();
	void update();
	void render();
	void shutdown();
private:
	VkSurfaceKHR surface;
};
