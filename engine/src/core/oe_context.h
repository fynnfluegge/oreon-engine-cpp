#pragma once

#include "platform\window.h"

namespace oe {

	class Context {

	public:
		static Context& getInstance();
		Window& getWindow();

	private:
		Context();
		static Context instance;
		Window window;
	};
}
