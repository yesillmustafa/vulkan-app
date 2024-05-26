#ifndef  TEXTURE_HPP
#define TEXTURE_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Device.h"
#include "Buffers.h"
#include "Model.h"

class Texture {
public:
	Texture(Device* devicePtr, Buffers* buffersPtr);

	void createTextureImage();
	void createTextureImageView();
	void createTextureSampler();

	VkImage& getTextureImage();
	VkImageView& getTextureImageView();
	VkDeviceMemory& getTextureImageMemory();
	VkSampler& getTextureSampler();
private:
	friend class DepthBuffer;

	Device* devicePtr;
	Buffers* buffersPtr;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory textureImageMemory;
	VkSampler textureSampler;

	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	
	VkImageView createImageView(VkImage image, VkFormat format);

};

#endif // ! TEXTURE_HPP
