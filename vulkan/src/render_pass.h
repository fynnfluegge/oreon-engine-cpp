#pragma once

#include <vulkan\vulkan.h>
#include <vector>

namespace vk {
	class RenderPass {
	public:
		RenderPass(VkDevice device);
		void createRenderPass();
	private:
		VkRenderPass handle;
		std::vector<VkAttachmentReference> colorReferences;
		const VkDevice deivce;
	};
}