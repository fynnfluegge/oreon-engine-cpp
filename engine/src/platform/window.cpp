#include "window.h"

Window::Window() {

}

void Window::create(int width, int height, const char* title) {

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	handle = glfwCreateWindow(width, height, "OE3", nullptr, nullptr);

	if (nullptr == handle) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
}

bool Window::isCloseRequested() {

	return glfwWindowShouldClose(handle);
}

void Window::shutdown() {

	glfwDestroyWindow(handle);
}

GLFWwindow* Window::getHandle() {
	return handle;
}