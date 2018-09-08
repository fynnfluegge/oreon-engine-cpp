#include "shader_module.h"
#include "util.h"

using namespace vk;


ShaderModule::ShaderModule(VkDevice device, const std::string& file, VkShaderStageFlagBits shaderStage) : device(device)
{
	createShaderModule(file);
	createShaderStage(shaderStage);
}

VkPipelineShaderStageCreateInfo ShaderModule::getShaderStageCreateInfo() const
{
	return shaderStageCreateInfo;
}

VkShaderModule ShaderModule::getHandle() const
{
	return handle;
}

void ShaderModule::destroy()
{
	vkDestroyShaderModule(device, handle, nullptr);
}

void ShaderModule::createShaderModule(const std::string& file)
{
	auto vertShaderCode = readFile(file);

	VkShaderModuleCreateInfo moduleCreateInfo = {};
	moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleCreateInfo.codeSize = vertShaderCode.size();
	moduleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(vertShaderCode.data());

	evaluateVkResult(vkCreateShaderModule(device, &moduleCreateInfo, nullptr, &handle),
		"Failed to create shader module");
}

void ShaderModule::createShaderStage(VkShaderStageFlagBits shaderStage)
{
	shaderStageCreateInfo = {};
	shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo.stage = shaderStage;
	shaderStageCreateInfo.module = handle;
	shaderStageCreateInfo.pName = "main";
	shaderStageCreateInfo.pSpecializationInfo = nullptr;
}
