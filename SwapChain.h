#ifndef  SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <algorithm>

#include "Device.h"
#include "VulkanWindow.h"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Buffers;
class DepthBuffer;

class SwapChain {
public:
    SwapChain(Device* devicePtr, VulkanWindow* windowPtr);
    SwapChain(Device* devicePtr, VulkanWindow* windowPtr, Buffers* buffersPtr);

    void createSwapChain();
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSwapchainKHR getSwapChain();

    void createImageViews();
    std::vector<VkImageView> getSwapChainImageViews();

    VkFormat getSwapChainImageFormat();
    VkExtent2D getSwapChainExtent();

    void recreateSwapChain();
    void cleanupSwapChain();

    void setBuffersPtr(Buffers* buffersPtr);
    void setDepthBuffersPtr(DepthBuffer* depthBufferPtr);


private:
    Device* devicePtr;
    VulkanWindow* windowPtr;
    Buffers* buffersPtr;
    DepthBuffer* depthBufferPtr;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    std::vector<VkImageView> swapChainImageViews;

};

#endif // ! SWAPCHAIN_HPP
