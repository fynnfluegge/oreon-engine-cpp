#pragma once#

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>

class VkContext {

public:
	static VkContext& getInstance();
	void init();
	VkInstance getVkInstance();
	std::vector<const char*> getEnabledLayers();

private:
	VkContext();
	static VkContext instance;
	VkInstance vkInstance;
	std::vector<const char*> enabledLayers;
};