#pragma once

#include <string>
#include <iostream>
#include <vulkan\vulkan_core.h>

namespace vk {

	std::string translateVkResult(VkResult vkResult);
	void evaluateVkResult(VkResult vkResult, std::string error_message);
}