#include "shader_pipeline.h"

using namespace vk;

ShaderPipeline::ShaderPipeline(VkDevice device) : device(device)
{
}

void ShaderPipeline::createShaderPipeline()
{
	shaderStageCreateInfos = std::vector< VkPipelineShaderStageCreateInfo>(shaderStages.size());

	for (ShaderModule shaderStage : shaderStages) {
		shaderStageCreateInfos.push_back(shaderStage.getShaderStageCreateInfo());
	}
}

void ShaderPipeline::createVertexShader(const std::string & file)
{
	shaderStages.push_back(ShaderModule(device, file, VK_SHADER_STAGE_VERTEX_BIT));
}

void ShaderPipeline::createTessellationControlShader(const std::string & file)
{
	shaderStages.push_back(ShaderModule(device, file, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT));
}

void ShaderPipeline::createTessellationEvaluationShader(const std::string & file)
{
	shaderStages.push_back(ShaderModule(device, file, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT));
}

void ShaderPipeline::createGeometryShader(const std::string & file)
{
	shaderStages.push_back(ShaderModule(device, file, VK_SHADER_STAGE_GEOMETRY_BIT));
}

void ShaderPipeline::createFragmentShader(const std::string & file)
{
	shaderStages.push_back(ShaderModule(device, file, VK_SHADER_STAGE_FRAGMENT_BIT));
}

void ShaderPipeline::addShaderModule(ShaderModule shaderModule)
{
	shaderStages.push_back(shaderModule);
}

void ShaderPipeline::destroy()
{
	for (ShaderModule shaderModule : shaderStages) {
			shaderModule.destroy();
	}
}

std::vector<VkPipelineShaderStageCreateInfo> ShaderPipeline::getShaderStageCreateInfos() const
{
	return shaderStageCreateInfos;
}
