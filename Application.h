#ifndef APPLICATION_HPP
#define APPLICATION_HPP


#include "VulkanWindow.h"
#include "Instance.h"
#include "ValidationManager.h"
#include "Device.h"
#include "SwapChain.h"
#include "Pipeline.h"
#include "Buffers.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "DescriptorSet.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include "DepthBuffer.h"
#include "Model.h"

class Application {
public:
    Application();
    ~Application();
    void run();
private:
    VulkanWindow* window;
    Instance* instance;
    ValidationManager* validationManager;
    Device* device;
    SwapChain* swapChain;
    Pipeline* pipeline;
    Buffers* buffers;
    Renderer* renderer;
    VertexBuffer* vertexBuffer;
    DescriptorSet* descriptorSet;
    UniformBuffer* uniformBuffer;
    Texture* texture;
    DepthBuffer* depthBuffer;
    Model* model;
    
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

};

#endif
