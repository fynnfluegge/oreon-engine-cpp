#pragma once

#include <vulkan\vulkan.h>
#include <vector>
#include <string>
#include "shader_module.h"

namespace vk {

	class ShaderPipeline {
	public:
		ShaderPipeline(VkDevice device);
		void createShaderPipeline();
		void createVertexShader(const std::string& file);
		void createTessellationControlShader(const std::string& file);
		void createTessellationEvaluationShader(const std::string& file);
		void createGeometryShader(const std::string& file);
		void createFragmentShader(const std::string& file);
		void addShaderModule(ShaderModule shaderModule);
		void destroy();
		std::vector<VkPipelineShaderStageCreateInfo> getShaderStageCreateInfos() const;

	private:
		std::vector<ShaderModule> shaderStages;
		std::vector<VkPipelineShaderStageCreateInfo> shaderStageCreateInfos;
		const VkDevice device;
	};
}
