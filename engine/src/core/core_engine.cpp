#include "core_engine.h"

using namespace std::chrono_literals;

int CoreEngine::fps;

CoreEngine::CoreEngine() : isRunning(false), frametime(1 / 2000.0f) {
}

void CoreEngine::init() {

	glfwInit();
	vk::Context::getInstance().init();
	oe::Context::getInstance().getWindow().create(800, 600, "OE3 Vulkan");
	renderEngine.init();
}

void CoreEngine::start() {
	if (isRunning)
		return;
	run();
}

void CoreEngine::run() {
	isRunning = true;

	int frames = 0;
	long frameCounter = 0;

	auto lastTime = std::chrono::high_resolution_clock::now();
	double unprocessedTime = 0;

	// Rendering Loop
	while (isRunning)
	{
		bool renderFrame = false;
		auto startTime = std::chrono::high_resolution_clock::now();
		long passedTime = static_cast<long>((startTime - lastTime).count());
		lastTime = startTime;

		unprocessedTime += passedTime / (double)1000000000;
		frameCounter += passedTime;

		while (unprocessedTime > frametime)
		{
			renderFrame = true;
			unprocessedTime -= frametime;

			if (oe::Context::getInstance().getWindow().isCloseRequested()) {
				stop();
			}
			
			this->update();

			if (frameCounter >= (double)1000000000)
			{
				fps = frames;
				frames = 0;
				frameCounter = 0;
				std::cout << fps << std::endl;
			}
		}
		if (renderFrame)
		{
			this->render();
			frames++;
		}
	}

	cleanUp();
}

void CoreEngine::stop() {
	if (!isRunning)
		return;

	isRunning = false;
}

void CoreEngine::render() {

	renderEngine.render();
}

void CoreEngine::update() {

	glfwPollEvents();
	renderEngine.update();
}

void CoreEngine::cleanUp() {
	oe::Context::getInstance().getWindow().shutdown();
}

int CoreEngine::getFps() {
	return fps;
}