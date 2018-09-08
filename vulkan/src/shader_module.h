#pragma once

#include <string>
#include <vulkan\vulkan.h>

namespace vk {

	class ShaderModule {
	public:
		ShaderModule(VkDevice device, const std::string& file, VkShaderStageFlagBits shaderStage);
		VkPipelineShaderStageCreateInfo getShaderStageCreateInfo() const;
		VkShaderModule getHandle() const;
		void destroy();
	private:
		VkShaderModule handle;
		VkPipelineShaderStageCreateInfo shaderStageCreateInfo;
		const VkDevice device;
		void createShaderModule(const std::string& file);
		void createShaderStage(VkShaderStageFlagBits shaderStage);
	};
}