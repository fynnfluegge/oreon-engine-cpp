#pragma once

#include <thread>
#include <iostream>
#include "platform\window.h"
#include "vk_context.h"
#include "context\oe_context.h"
#include "render_engine.h"

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
