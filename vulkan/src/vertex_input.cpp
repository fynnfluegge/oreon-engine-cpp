#include "vertex_input.h"

using namespace vk;

VertexInput::VertexInput(VertexLayout layout)
{
	switch (layout) {
		case POS2D:
			createBindingDescription(0, 1, sizeof(float) * 2);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32_SFLOAT, 0);
			break;
		case POS:
			createBindingDescription(0, 1, sizeof(float) * 3);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
			break;
		case POS_UV:
			createBindingDescription(0, 2, sizeof(float) * 5);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
			addVertexAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 3);
			break;
		case POS2D_UV:
			createBindingDescription(0, 2, sizeof(float) * 4);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32_SFLOAT, 0);
			addVertexAttributeDescription(0, 1, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 2);
			break;
		case POS_NORMAL:
			createBindingDescription(0, 2, sizeof(float) * 6);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
			addVertexAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 3);
			break;
		case POS_NORMAL_UV:
			createBindingDescription(0, 3, sizeof(float) * 8);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
			addVertexAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 3);
			addVertexAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 6);
			break;
		case POS_NORMAL_UV_TAN_BITAN:
			createBindingDescription(0, 5, sizeof(float) * 14);
			addVertexAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
			addVertexAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 3);
			addVertexAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT, sizeof(float) * 6);
			addVertexAttributeDescription(0, 3, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 8);
			addVertexAttributeDescription(0, 4, VK_FORMAT_R32G32B32_SFLOAT, sizeof(float) * 11);
			break;
		default: break;
	}
}

VkVertexInputBindingDescription VertexInput::getBindingDescription() const
{
	return bindingDescription;
}

std::vector<VkVertexInputAttributeDescription> VertexInput::getAttributeDescriptions() const
{
	return attributeDescriptions;
}

void VertexInput::createBindingDescription(uint32_t binding, int attributeCount, uint32_t stride)
{
	bindingDescription = {};
	bindingDescription.binding = binding;
	bindingDescription.stride = stride;
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	attributeDescriptions = std::vector<VkVertexInputAttributeDescription>(attributeCount);
}

void VertexInput::addVertexAttributeDescription(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset)
{
	VkVertexInputAttributeDescription attributeDescription = {};
	attributeDescription.binding = binding;
	attributeDescription.location = location;
	attributeDescription.format = format;
	attributeDescription.offset = offset;

	attributeDescriptions.push_back(attributeDescription);
}
