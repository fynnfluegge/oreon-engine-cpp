#pragma once#

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>
#include "deviceManager.h"

class VkContext {

public:
	static VkContext& getInstance();
	void init();
	VkInstance& getVkInstance();
	DeviceManager& getDeviceManager();
	std::vector<const char*> getEnabledLayers();

private:
	VkContext();
	static VkContext instance;
	VkInstance vkInstance;
	DeviceManager deviceManager;
	VkDebugReportCallbackEXT callback;
	bool checkValidationLayerSupport();
	bool checkExtensionSupport(std::vector<const char*> extensions);
	std::vector<const char*> getRequiredExtensions();
	void setupDebugCallback();
	VkResult CreateDebugReportCallbackEXT(VkInstance instance,
		const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
		VkDebugReportCallbackEXT* pCallback);
	std::vector<const char*> enabledLayers;
	static VKAPI_ATTR VkBool32 VKAPI_CALL MyDebugReportCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);
};