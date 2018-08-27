#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class Semaphore {
	public:
		Semaphore(VkDevice device);
		void destroy();
	private:
		VkSemaphore handle;
		const VkDevice device;
	};
}