#include "VkContext.h"


VkContext::VkContext() {

}

VkContext VkContext::instance;
VkContext& VkContext::getInstance() {
	return instance;
}

void VkContext::init() {
	if (!glfwVulkanSupported()) {
		std::cout << "ERROR: Vulkan not supported" << std::endl;
	}
}