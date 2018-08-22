#include "renderEngine.h"

void RenderEngine::init() {

	glfwCreateWindowSurface(vk::Context::getInstance().getVkInstance(),
		oe::Context::getInstance().getWindow().getHandle(), nullptr, &surface);

	PhysicalDevice physicalDevice(surface);
}

void RenderEngine::update() {

}

void RenderEngine::render() {

}

void RenderEngine::shutdown() {

}