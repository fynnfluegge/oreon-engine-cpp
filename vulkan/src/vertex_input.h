#pragma once

#include <vector>
#include <vulkan\vulkan.h>

namespace vk {

	enum VertexLayout
	{
		POS_NORMAL_UV_TAN_BITAN,
		POS_NORMAL,
		POS_UV,
		POS,
		POS_NORMAL_UV,
		POS2D,
		POS2D_UV
	};

	class VertexInput {
	public:
		VertexInput(VertexLayout layout);
	private:
		VkVertexInputBindingDescription bindingDescription;
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
		void createBindingDescription(uint32_t binding, int attributeCount, uint32_t stride);
		void addVertexAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset);
	};
}
