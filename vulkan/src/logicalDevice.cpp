#include "logicalDevice.h"

#include "util\util.h"

using namespace vk;

LogicalDevice::LogicalDevice(PhysicalDevice physicalDevice)
{
	int queueCeateInfoCount = 3;

	graphicsQueueFamilyIndex = physicalDevice.getGraphicsAndPresentationQueueFamily().index;
	computeQueueFamilyIndex = physicalDevice.getComputeExclusiveQueueFamily().index;

	if (computeQueueFamilyIndex == -1) {
		std::cout << "No compute exclusive queue available on device : " << physicalDevice.getProperties().deviceName << std::endl;
		queueCeateInfoCount--;
		computeQueueFamilyIndex = physicalDevice.getComputeQueueFamily().index;
		if (computeQueueFamilyIndex == -1) {
			std::cout << "No compute queue available on device : " << physicalDevice.getProperties().deviceName << std::endl;
		}
	}
	transferQueueFamilyIndex = physicalDevice.getTransferExclusiveQueueFamily().index;
	if (transferQueueFamilyIndex == -1) {
		std::cout << "No transfer exclusive queue available on device: " << physicalDevice.getProperties().deviceName << std::endl;
		queueCeateInfoCount--;
		transferQueueFamilyIndex = physicalDevice.getTransferQueueFamily().index;
		if (transferQueueFamilyIndex == -1) {
			std::cout << "No transfer queue available on device: " << physicalDevice.getProperties().deviceName << std::endl;
		}
	}

	VkDeviceQueueCreateInfo* queueCreateInfos = new VkDeviceQueueCreateInfo[queueCeateInfoCount];
	float queue_priorities[1] = { 0.0 };

	VkDeviceQueueCreateInfo graphicsQueueCreateInfo = {};
	graphicsQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	graphicsQueueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
	graphicsQueueCreateInfo.queueCount = 1;
	graphicsQueueCreateInfo.pQueuePriorities = queue_priorities;
		
	queueCreateInfos[0] = graphicsQueueCreateInfo;

	if (graphicsQueueFamilyIndex != computeQueueFamilyIndex) {
		VkDeviceQueueCreateInfo computeQueueCreateInfo = {};
		computeQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		computeQueueCreateInfo.queueFamilyIndex = computeQueueFamilyIndex;
		computeQueueCreateInfo.queueCount = 1;
		computeQueueCreateInfo.pQueuePriorities = queue_priorities;

		queueCreateInfos[1] = computeQueueCreateInfo;
	}

	if (graphicsQueueFamilyIndex != transferQueueFamilyIndex &&
		 computeQueueFamilyIndex != transferQueueFamilyIndex) {
		VkDeviceQueueCreateInfo transferQueueCreateInfo = {};
		transferQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		transferQueueCreateInfo.queueFamilyIndex = transferQueueFamilyIndex;
		transferQueueCreateInfo.queueCount = 1;
		transferQueueCreateInfo.pQueuePriorities = queue_priorities;

		queueCreateInfos[2] = transferQueueCreateInfo;
	}

	VkPhysicalDeviceFeatures physicalDeviceFeatures = {};
	physicalDeviceFeatures.tessellationShader = VK_TRUE;
	physicalDeviceFeatures.geometryShader = VK_TRUE;

	const char *extension_names = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	if (!physicalDevice.isExtensionSupported(extension_names)) {
		std::cerr << "Extension " << extension_names << " not supported" << std::endl;
	}

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pNext = VK_NULL_HANDLE;
	deviceCreateInfo.pQueueCreateInfos = queueCreateInfos;
	deviceCreateInfo.queueCreateInfoCount = queueCeateInfoCount;
	deviceCreateInfo.ppEnabledExtensionNames = &extension_names;
	deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

	evaluateVkResult(vkCreateDevice(physicalDevice.getHandle(), &deviceCreateInfo, NULL, &handle),
		"Failed to create logical device");
}

VkQueue LogicalDevice::getDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex)
{
	VkQueue queue;
	vkGetDeviceQueue(handle, queueFamilyIndex, queueIndex, &queue);
	return queue;
}

VkDevice LogicalDevice::getHandle() const
{
	return handle;
}
