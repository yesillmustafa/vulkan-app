#ifndef DEPTHBUFFER_HPP
#define DEPTHBUFFER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Device.h"
#include "Texture.h"
#include "SwapChain.h"

class DepthBuffer {
public:
	DepthBuffer(Device* devicePtr, Texture* texturePtr, SwapChain* swapChainPtr);

	void createDepthResources();

	VkImage& getDepthImage();
	VkDeviceMemory& getDepthImageMemory();
	VkImageView& getDepthImageView();
private:
	friend class Pipeline;

	Device* devicePtr;
	Texture* texturePtr;
	SwapChain* swapChainPtr;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
};

#endif // !DEPTHBUFFER_HPP
