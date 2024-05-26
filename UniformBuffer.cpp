#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(Device* devicePtr, Buffers* buffersPtr, VertexBuffer* vertexBufferPtr, SwapChain* swapChainPtr) : 
    devicePtr(devicePtr), 
    buffersPtr(buffersPtr), 
    vertexBufferPtr(vertexBufferPtr),
    swapChainPtr(swapChainPtr)
{
}

void UniformBuffer::createUniformBuffers()
{
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(buffersPtr->MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < buffersPtr->MAX_FRAMES_IN_FLIGHT; i++) {
        buffersPtr->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(devicePtr->getDevice(), uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }
}

std::vector<VkBuffer>& UniformBuffer::getUniformBuffers()
{
    return uniformBuffers;
}

std::vector<VkDeviceMemory>& UniformBuffer::getUniformBuffersMemory()
{
    return uniformBuffersMemory;
}

void UniformBuffer::updateUniformBuffer(uint32_t currentImage)
{
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), swapChainPtr->getSwapChainExtent().width / (float)swapChainPtr->getSwapChainExtent().height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}