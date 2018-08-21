#include "renderEngine.h"

void RenderEngine::init() {

	glfwCreateWindowSurface(VkContext::getInstance().getVkInstance(),
		EngineContext::getInstance().getWindow().getHandle(), nullptr, &surface);

	PhysicalDevice physicalDevice(surface);
}

void RenderEngine::update() {

}

void RenderEngine::render() {

}

void RenderEngine::shutdown() {

}