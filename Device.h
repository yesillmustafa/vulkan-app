#ifndef DEVICE_HPP
#define DEVICE_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <stdexcept>
#include <set>
#include <optional>

#include "Instance.h"
#include "VulkanWindow.h"

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class SwapChain;

class Device {
public:
	Device(Instance* instance, VulkanWindow* window);
	Device(Instance* instance, VulkanWindow* window, SwapChain* swapChain);
	void pickPhysicalDevice();
	void createLogicalDevice();
	VkPhysicalDevice getPhysicalDevice();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	VkDevice getDevice();
	void setSwapChain(SwapChain* swapChainPtr);

	VkQueue getGraphicsQueue();
	VkQueue getPresentQueue();

private:
	Instance* instancePtr;
	VulkanWindow* windowPtr;
	SwapChain* swapChainPtr;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	

	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};

#endif // !DEVICE_HPP

