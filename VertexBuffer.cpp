#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Device* devicePtr, Buffers* buffersPtr) : devicePtr(devicePtr), buffersPtr(buffersPtr)
{
}

void VertexBuffer::createVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    buffersPtr->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(devicePtr->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(devicePtr->getDevice(), stagingBufferMemory);

    buffersPtr->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    buffersPtr->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(devicePtr->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(devicePtr->getDevice(), stagingBufferMemory, nullptr);
}

VkBuffer& VertexBuffer::getVertexBuffer()
{
    return vertexBuffer;
}

VkDeviceMemory_T*& VertexBuffer::getVertexBufferMemory()
{
    return vertexBufferMemory;
}

void VertexBuffer::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    buffersPtr->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(devicePtr->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(devicePtr->getDevice(), stagingBufferMemory);

    buffersPtr->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    buffersPtr->copyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(devicePtr->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(devicePtr->getDevice(), stagingBufferMemory, nullptr);
}

VkBuffer& VertexBuffer::getIndexBuffer()
{
    return indexBuffer;
}

VkDeviceMemory_T*& VertexBuffer::getIndexBufferMemory()
{
    return indexBufferMemory;
}
