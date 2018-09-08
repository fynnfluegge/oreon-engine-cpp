#pragma once

#include <vector>
#include <vulkan\vulkan.h>

#include "entity\vertex.h"

namespace vk {

	class VertexInput {
	public:
		VertexInput(VertexLayout layout);
		VkVertexInputBindingDescription getBindingDescription() const;
		std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() const;
	private:
		VkVertexInputBindingDescription bindingDescription;
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
		void createBindingDescription(uint32_t binding, int attributeCount, uint32_t stride);
		void addVertexAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset);
	};
}
