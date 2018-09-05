#pragma once

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <GLFW/glfw3.h>
#include "vk_context.h"
#include "oe_context.h"

class RenderEngine {

public:
	void init();
	void update();
	void render();
	void shutdown();
private:
	VkSurfaceKHR surface;
};
