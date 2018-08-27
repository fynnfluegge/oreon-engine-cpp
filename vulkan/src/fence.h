#pragma once

#include "vulkan\vulkan.h"

namespace vk {

	class Fence {
	public:
		Fence(VkDevice device);
		void reset();
		void wait();
		void destroy();
		VkFence getHandle();
	private:
		VkFence handle;
		const VkDevice device;
	};
}
