#pragma once

#include <iostream>
#include <GLFW\glfw3.h>

class Window {

public:
	void create(int width, int height, const char* title);
	void shutdown();
	GLFWwindow* getHandle();
	bool isCloseRequested();
	int getWidth();
	int getHeight();
	void setWidth(const int width);
	void setHeight(const int height);


private:
	GLFWwindow* handle;
	int width;
	int height;
};
