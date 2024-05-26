#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <fstream>
#include <vector>
#include <string>

#include "Device.h"
#include "SwapChain.h"
#include "Vertex.h"

class DescriptorSet;
class DepthBuffer;

class Pipeline {
public:
	Pipeline(Device* devicePtr, SwapChain* swapChainPtr);

	void createGraphicsPipeline();
	void createRenderPass();

	VkRenderPass& getRenderPass();
	VkPipelineLayout& getPipelineLayout();
	VkPipeline& getGraphicsPipeline();

	void setDescriptorSet(DescriptorSet* descriptorSet);
	void setDepthBuffer(DepthBuffer* depthBuffer);

private:
	Device* devicePtr;
	SwapChain* swapChainPtr;
	DescriptorSet* descriptorSetPtr;
	DepthBuffer* depthBufferPtr;

	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	Vertex vertex;

};


#endif // !PIPELINE_HPP
