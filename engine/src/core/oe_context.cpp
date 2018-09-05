#include "oe_context.h"

using namespace oe;

Context::Context(){}

Context Context::instance;
Context& Context::getInstance() {
	return instance;
}

Window& Context::getWindow() {
	return window;
}