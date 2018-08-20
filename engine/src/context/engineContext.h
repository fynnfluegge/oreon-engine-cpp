#pragma once

#include "platform\window.h"

class EngineContext {

public:
	static EngineContext& getInstance();
	Window& getWindow();

private:
	EngineContext();
	static EngineContext instance;
	Window window;
};
