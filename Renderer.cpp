#include "Renderer.h"
#include "UniformBuffer.h"

Renderer::Renderer(Device* devicePtr, SwapChain* swapChainPtr, Buffers* buffersPtr, VulkanWindow* windowPtr) : 
    devicePtr(devicePtr), 
    swapChainPtr(swapChainPtr), 
    buffersPtr(buffersPtr), 
    windowPtr(windowPtr),
    uniformBufferPtr(nullptr)
{
    

}

void Renderer::drawFrame()
{
    commandBuffers = buffersPtr->getCommandBuffers();

    vkWaitForFences(devicePtr->getDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(devicePtr->getDevice(), swapChainPtr->getSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        swapChainPtr->recreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    uniformBufferPtr->updateUniformBuffer(currentFrame);

    vkResetFences(devicePtr->getDevice(), 1, &inFlightFences[currentFrame]);

    vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
    buffersPtr->recordCommandBuffer(commandBuffers[currentFrame],currentFrame ,imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[currentFrame];

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(devicePtr->getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { swapChainPtr->getSwapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(devicePtr->getPresentQueue(), &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || windowPtr->getFramebufferResized()) {
        windowPtr->setFramebufferResized(false);
        swapChainPtr->recreateSwapChain();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    currentFrame = (currentFrame + 1) % buffersPtr->MAX_FRAMES_IN_FLIGHT;
}

void Renderer::createSyncObjects()
{
    commandBuffers = buffersPtr->getCommandBuffers();

    imageAvailableSemaphores.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphores.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);
    inFlightFences.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    

    for (size_t i = 0; i < 2; i++) {
        if (vkCreateSemaphore(devicePtr->getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(devicePtr->getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(devicePtr->getDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {

            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }

}

VkSemaphore Renderer::getImageAvailableSemaphore()
{
    return imageAvailableSemaphore;
}

VkSemaphore Renderer::getRenderFinishedSemaphore()
{
    return renderFinishedSemaphore;
}

VkFence Renderer::getInFlightFence()
{
    return inFlightFence;
}

std::vector<VkCommandBuffer>& Renderer::getCommandBuffers()
{
    return commandBuffers;
}

std::vector<VkSemaphore>& Renderer::getImageAvailableSemaphores()
{
    return imageAvailableSemaphores;
}

std::vector<VkSemaphore>& Renderer::getRenderFinishedSemaphores()
{
    return renderFinishedSemaphores;
}

std::vector<VkFence>& Renderer::getInFlightFences()
{
    return inFlightFences;
}

void Renderer::setUniformBuffer(UniformBuffer* uniformBuffer)
{
    this->uniformBufferPtr = uniformBuffer;
}

uint32_t& Renderer::getCurrentFrame()
{
    return currentFrame;
}
