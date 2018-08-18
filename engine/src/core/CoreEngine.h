#pragma once

#include <thread>
#include <iostream>
#include "platform\window.h"
#include "context\VkContext.h"

class CoreEngine {

public:
	CoreEngine();
	void init();
	void start();
	static int getFps();

private:
	void run();
	void stop();
	void render();
	void update();
	void cleanUp();
	static int fps;
	double frametime;
	bool isRunning;
	Window window;
};
