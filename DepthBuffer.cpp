#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(Device* devicePtr, Texture* texturePtr, SwapChain* swapChainPtr) : devicePtr(devicePtr), texturePtr(texturePtr), swapChainPtr(swapChainPtr)
{
}

void DepthBuffer::createDepthResources()
{
    VkFormat depthFormat = findDepthFormat();

    texturePtr->createImage(swapChainPtr->getSwapChainExtent().width, swapChainPtr->getSwapChainExtent().height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
    depthImageView =  texturePtr->createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);
}

VkImage& DepthBuffer::getDepthImage()
{
    return depthImage;
}

VkDeviceMemory& DepthBuffer::getDepthImageMemory()
{
    return depthImageMemory;
}

VkImageView& DepthBuffer::getDepthImageView()
{
    return depthImageView;
}

VkFormat DepthBuffer::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
    for (VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(devicePtr->getPhysicalDevice(), format, &props);

        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        }
        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("failed to find supported format!");
}

VkFormat DepthBuffer::findDepthFormat()
{
    return findSupportedFormat(
        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
}

bool DepthBuffer::hasStencilComponent(VkFormat format)
{
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}
