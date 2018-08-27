#include "submit_info.h"
#include "util.h"

using namespace vk;

SubmitInfo::SubmitInfo()
{
	handle = {};
	handle.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
}

void SubmitInfo::setCommandBuffer(VkCommandBuffer& buffer)
{
	handle.pCommandBuffers = &buffer;
	handle.commandBufferCount = 1;
}

void SubmitInfo::setWaitSemaphore(VkSemaphore& semaphore)
{
	handle.pWaitSemaphores = &semaphore;
	handle.waitSemaphoreCount = 1;
}

void SubmitInfo::setSignalSemaphore(VkSemaphore& semaphore)
{
	handle.pSignalSemaphores = &semaphore;
	handle.signalSemaphoreCount = 1;
}

void SubmitInfo::setWaitDstStageMask(VkPipelineStageFlags flag)
{
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	handle.pWaitDstStageMask = waitStages;
}

void SubmitInfo::clearWaitSemaphores()
{
	handle.pWaitSemaphores = nullptr;
	handle.waitSemaphoreCount = 0;
}

void SubmitInfo::clearSignalSemaphores()
{
	handle.pSignalSemaphores = nullptr;
	handle.signalSemaphoreCount = 0;
}

void SubmitInfo::submit(VkQueue queue)
{
	evaluateVkResult(vkQueueSubmit(queue, 1, &handle, VK_NULL_HANDLE),  "Failed to submit to queue");
}

void vk::SubmitInfo::submit(VkQueue queue, VkFence fence)
{
	evaluateVkResult(vkQueueSubmit(queue, 1, &handle, fence), "Failed to submit to queue");
}
