#pragma once

#include <iostream>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <vector>
#include <vulkan/vulkan.h>
#include "physicalDevice.h"
#include "logicalDevice.h"

namespace vk {

	enum class DeviceType {
		MAJOR_GRAPHICS_DEVICE,
		SECONDARY_GRAPHICS_DEVICE,
		COMPUTING_DEVICE,
		SLI_DISCRETE_DEVICE0,
		SLI_DISCRETE_DEVICE1
	};

	struct DeviceBundle {
		PhysicalDevice physicalDevice;
		LogicalDevice logicalDevice;
		DeviceBundle(PhysicalDevice x, LogicalDevice y) : physicalDevice(x), logicalDevice(y) {};
	};

	class Context {

	public:
		static Context& getInstance();
		void init();
		const VkInstance& getVkInstance();
		std::vector<const char*> getEnabledLayers();
		void addDevice(DeviceType devicetype, PhysicalDevice physicalDevice, LogicalDevice logicalDevice);
		DeviceBundle getDevice(DeviceType deviceType);

	private:
		Context();
		static Context instance;
		VkInstance vkInstance;
		std::unordered_map<DeviceType, DeviceBundle> devices;

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

}