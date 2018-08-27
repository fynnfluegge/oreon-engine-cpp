#pragma once

#include <vulkan\vulkan.h>
#include "commandbuffer.h"
#include "fence.h"

namespace vk {

	class SubmitInfo {
	public:
		SubmitInfo();
		void setCommandBuffer(VkCommandBuffer& buffer);
		void setWaitSemaphore(VkSemaphore& semaphore);
		void setSignalSemaphore(VkSemaphore& semaphore);
		void setWaitDstStageMask(VkPipelineStageFlags flag);
		void clearWaitSemaphores();
		void clearSignalSemaphores();
		void submit(VkQueue queue);
		void submit(VkQueue queue, VkFence fence);
	private:
		VkSubmitInfo handle;
	};
}
