#include "engineContext.h"

EngineContext::EngineContext(){}

EngineContext EngineContext::instance;
EngineContext& EngineContext::getInstance() {
	return instance;
}

Window& EngineContext::getWindow() {
	return window;
}