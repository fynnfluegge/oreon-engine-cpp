#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <vulkan\vulkan_core.h>

namespace vk {

	std::string translateVkResult(VkResult vkResult);
	void evaluateVkResult(VkResult vkResult, std::string error_message);
	VkSampleCountFlagBits getSampleCountBit(uint32_t samples);
	uint32_t getMemoryTypeIndex(VkPhysicalDeviceMemoryProperties memoryProperties,
		uint32_t memoryTypeBits, VkMemoryPropertyFlags properties);
	std::vector<char> readFile(const std::string& filename);
}