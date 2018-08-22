#pragma once

#include <thread>
#include <iostream>
#include "platform\window.h"
#include "vkContext.h"
#include "context\oeContext.h"
#include "renderEngine.h"

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
	RenderEngine renderEngine;
};
