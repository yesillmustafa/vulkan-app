#ifndef  RENDERER_HPP
#define RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Device.h"
#include "SwapChain.h"
#include "Buffers.h"
#include "VulkanWindow.h"

class UniformBuffer;

class Renderer {
public:
	Renderer(Device* devicePtr, SwapChain* swapChainPtr, Buffers* buffersPtr, VulkanWindow* windowPtr);

	void drawFrame();
	void createSyncObjects();
	
	VkSemaphore getImageAvailableSemaphore();
	VkSemaphore getRenderFinishedSemaphore();
	VkFence getInFlightFence();

	std::vector<VkCommandBuffer>& getCommandBuffers();
	std::vector<VkSemaphore>& getImageAvailableSemaphores();
	std::vector<VkSemaphore>& getRenderFinishedSemaphores();
	std::vector<VkFence>& getInFlightFences();

	void setUniformBuffer(UniformBuffer* uniformBuffer);

	uint32_t& getCurrentFrame();

private:
	Device* devicePtr;
	SwapChain* swapChainPtr;
	Buffers* buffersPtr;
	VulkanWindow* windowPtr;
	UniformBuffer* uniformBufferPtr;
	
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;

	uint32_t currentFrame = 0;

	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

};

#endif // ! RENDERER_HPP
