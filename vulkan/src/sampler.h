#pragma once

#include <vulkan\vulkan.h>

namespace vk {

	class Sampler {
	public:
		Sampler(VkDevice device, VkFilter filterMode, VkBool32 anistropic,
			float maxAnistropy, VkSamplerMipmapMode mipmapMode, float maxLod,
			VkSamplerAddressMode addressMode);
		void destroy();
	private:
		VkSampler handle;
		const VkDevice device;
	};
}
