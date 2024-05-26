#ifndef DESCRIPTORSET_HPP
#define DESCRIPTORSET_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Device.h"
#include "Buffers.h"

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class UniformBuffer;
class Texture;

class DescriptorSet {
public:
    DescriptorSet(Device* devicePtr, Buffers* buffersPtr);

    void createDescriptorSetLayout();
    VkDescriptorSetLayout& getDescriptorSetLayout();

    void createDescriptorPool();
    VkDescriptorPool& getDescriptorPool();

    void createDescriptorSets();
    std::vector<VkDescriptorSet>& getDescriptorSets();

    void setUniformBuffer(UniformBuffer* uniformBuffer);
    void setTexture(Texture* texture);

private:
    Device* devicePtr;
    Buffers* buffersPtr;
    UniformBuffer* uniformBufferPtr;
    Texture* texturePtr;

    VkDescriptorSetLayout descriptorSetLayout;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
};

#endif // !DESCRIPTORSET_HPP
