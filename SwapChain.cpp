#include "SwapChain.h"
#include "Buffers.h"
#include "DepthBuffer.h"

SwapChain::SwapChain(Device* devicePtr, VulkanWindow* windowPtr) : devicePtr(devicePtr), windowPtr(windowPtr), buffersPtr(nullptr), depthBufferPtr(nullptr)
{
}

SwapChain::SwapChain(Device* devicePtr, VulkanWindow* windowPtr, Buffers* buffersPtr) : devicePtr(devicePtr), windowPtr(windowPtr), buffersPtr(buffersPtr)
{
}

void SwapChain::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(devicePtr->getPhysicalDevice());

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	unsigned int imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = windowPtr->getSurface();

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = devicePtr->findQueueFamilies(devicePtr->getPhysicalDevice());
	unsigned int queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(devicePtr->getDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	vkGetSwapchainImagesKHR(devicePtr->getDevice(), swapChain, &imageCount, nullptr);
	swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(devicePtr->getDevice(), swapChain, &imageCount, swapChainImages.data());

	swapChainImageFormat = surfaceFormat.format;
	swapChainExtent = extent;
}

SwapChainSupportDetails SwapChain::querySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, windowPtr->getSurface(), &(details.capabilities));

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, windowPtr->getSurface(), &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, windowPtr->getSurface(), &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, windowPtr->getSurface(), &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, windowPtr->getSurface(), &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSwapchainKHR SwapChain::getSwapChain()
{
	return swapChain;
}

void SwapChain::createImageViews()
{
	swapChainImageViews.resize(swapChainImages.size());

	for (size_t i = 0; i < swapChainImages.size(); i++) {
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = swapChainImageFormat;
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(devicePtr->getDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create image views!");
		}
	}
}

std::vector<VkImageView> SwapChain::getSwapChainImageViews()
{
	return swapChainImageViews;
}

VkFormat SwapChain::getSwapChainImageFormat()
{
	return swapChainImageFormat;
}

VkExtent2D SwapChain::getSwapChainExtent()
{
	return swapChainExtent;
}

void SwapChain::recreateSwapChain()
{
	int width = 0, height = 0;
	glfwGetFramebufferSize(windowPtr->getWindow(), &width, &height);
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(windowPtr->getWindow(), &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(devicePtr->getDevice());

	cleanupSwapChain();

	createSwapChain();
	createImageViews();
	depthBufferPtr->createDepthResources();
	buffersPtr->createFramebuffers();
}

void SwapChain::cleanupSwapChain()
{
	vkDestroyImageView(devicePtr->getDevice(), depthBufferPtr->getDepthImageView(), nullptr);
	vkDestroyImage(devicePtr->getDevice(), depthBufferPtr->getDepthImage(), nullptr);
	vkFreeMemory(devicePtr->getDevice(), depthBufferPtr->getDepthImageMemory(), nullptr);

	for (auto framebuffer : buffersPtr->getSwapChainFramebuffers()) {
		vkDestroyFramebuffer(devicePtr->getDevice(), framebuffer, nullptr);
	}

	for (auto imageView : swapChainImageViews) {
		vkDestroyImageView(devicePtr->getDevice(), imageView, nullptr);
	}

	vkDestroySwapchainKHR(devicePtr->getDevice(), swapChain, nullptr);
}

void SwapChain::setBuffersPtr(Buffers* buffersPtr)
{
	this->buffersPtr = buffersPtr;
}

void SwapChain::setDepthBuffersPtr(DepthBuffer* depthBufferPtr)
{
	this->depthBufferPtr = depthBufferPtr;
}

VkSurfaceFormatKHR SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		int width, height;
		glfwGetFramebufferSize(windowPtr->getWindow(), &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}
