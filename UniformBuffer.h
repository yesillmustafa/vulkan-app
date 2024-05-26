#ifndef UNIFORMBUFFER_HPP
#define UNIFORMBUFFER_HPP


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

#include "Device.h"
#include "Buffers.h"
#include "DescriptorSet.h"
#include "VertexBuffer.h"
#include "SwapChain.h"

class UniformBuffer {
public:
	UniformBuffer(Device* devicePtr, Buffers* buffersPtr, VertexBuffer* vertexBufferPtr, SwapChain* swapChainPtr);

	void createUniformBuffers();

	std::vector<VkBuffer>& getUniformBuffers();
	std::vector<VkDeviceMemory>& getUniformBuffersMemory();

	void updateUniformBuffer(uint32_t currentImage);


private:
	Device* devicePtr;
	Buffers* buffersPtr;
	VertexBuffer* vertexBufferPtr;
	SwapChain* swapChainPtr;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
};

#endif // !UNIFORMBUFFER_HPP
