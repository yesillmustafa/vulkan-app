#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

#include "Device.h"
#include "SwapChain.h"
#include "Pipeline.h"

class VertexBuffer;
class DescriptorSet;
class Renderer;
class DepthBuffer;

class Buffers {
public:
	Buffers(Device* devicePtr, SwapChain* swapChainPtr, Pipeline* pipelinePtr);
	Buffers(Device* devicePtr, SwapChain* swapChainPtr, Pipeline* pipelinePtr, VertexBuffer* vertexBufferPtr);
	void createFramebuffers();

	std::vector<VkFramebuffer> getSwapChainFramebuffers();

	void createCommandPool();

	void createCommandBuffer();

	void recordCommandBuffer(VkCommandBuffer commandBuffer,uint32_t currentFrame ,uint32_t imageIndex);

	VkCommandPool& getCommandPool();
	VkCommandBuffer& getCommandBuffer();

	const int MAX_FRAMES_IN_FLIGHT = 2;

	std::vector<VkCommandBuffer>& getCommandBuffers();

	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void setDescriptorSet(DescriptorSet* descriptorSet);
	void setRenderer(Renderer* renderer);
	void setDepthBuffer(DepthBuffer* depthBufferPtr);


private:
	friend class VertexBuffer;
	friend class UniformBuffer;
	friend class Texture;

	Device* devicePtr;
	SwapChain* swapChainPtr;
	Pipeline* pipelinePtr;
	VertexBuffer* vertexBufferPtr;
	DescriptorSet* descriptorSetPtr;
	Renderer* rendererPtr;
	DepthBuffer* depthBufferPtr;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;

	std::vector<VkCommandBuffer> commandBuffers;

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);


};

#endif // !BUFFERS_HPP
