#include "sampler.h"
#include "util\util.h"

using namespace vk;

Sampler::Sampler(VkDevice device, VkFilter filterMode, VkBool32 anistropic, float maxAnistropy,
	VkSamplerMipmapMode mipmapMode, float maxLod, VkSamplerAddressMode addressMode) : device(device)
{
	VkSamplerCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	createInfo.magFilter = filterMode;
	createInfo.minFilter = filterMode;
	createInfo.addressModeU = addressMode;
	createInfo.addressModeV = addressMode;
	createInfo.addressModeW = addressMode;
	createInfo.anisotropyEnable = anistropic;
	createInfo.maxAnisotropy = maxAnistropy;
	createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	createInfo.unnormalizedCoordinates = VK_FALSE;
	createInfo.compareEnable = VK_FALSE;
	createInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	createInfo.mipmapMode = mipmapMode;
	createInfo.mipLodBias = 0;
	createInfo.minLod = 0;
	createInfo.maxLod = maxLod;

	evaluateVkResult(vkCreateSampler(device, &createInfo, nullptr, &handle),
		"Failed to create sampler");
}

void Sampler::destroy()
{
	vkDestroySampler(device, handle, nullptr);
}
