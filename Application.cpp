#include "Application.h"


Application::Application() {
    instance = new Instance();
    window = new VulkanWindow(instance);
    device = new Device(instance, window);
    swapChain = new SwapChain(device, window);
    device->setSwapChain(swapChain);
    pipeline = new Pipeline(device,swapChain);
    buffers = new Buffers(device, swapChain, pipeline);
    swapChain->setBuffersPtr(buffers);
    renderer = new Renderer(device, swapChain, buffers, window);
    buffers->setRenderer(renderer);
    vertexBuffer = new VertexBuffer(device,buffers);
    buffers->setVertexBuffer(vertexBuffer);
    descriptorSet = new DescriptorSet(device, buffers);
    pipeline->setDescriptorSet(descriptorSet);
    uniformBuffer = new UniformBuffer(device, buffers, vertexBuffer,swapChain);
    renderer->setUniformBuffer(uniformBuffer);
    descriptorSet->setUniformBuffer(uniformBuffer);
    buffers->setDescriptorSet(descriptorSet);
    texture = new Texture(device, buffers);
    descriptorSet->setTexture(texture);
    depthBuffer = new DepthBuffer(device, texture, swapChain);
    pipeline->setDepthBuffer(depthBuffer);
    buffers->setDepthBuffer(depthBuffer);
    swapChain->setDepthBuffersPtr(depthBuffer);
    model = new Model();

}

Application::~Application()
{
    delete instance;
    delete window;
    delete device;
    delete swapChain;
    delete pipeline;
    delete buffers;
    delete renderer;
    delete vertexBuffer;
    delete descriptorSet;
    delete uniformBuffer;
    delete texture;
    delete depthBuffer;
    delete model;

}

void Application::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Application::initWindow()
{
    window->init();
}

void Application::initVulkan()
{
    instance->createInstance();
    instance->getValidationManager()->setupDebugMessenger(instance->getInstance());
    window->createSurface();
    device->pickPhysicalDevice();
    device->createLogicalDevice();
    swapChain->createSwapChain();
    swapChain->createImageViews();
    pipeline->createRenderPass();
    descriptorSet->createDescriptorSetLayout();
    pipeline->createGraphicsPipeline();
    buffers->createCommandPool();
    depthBuffer->createDepthResources();
    buffers->createFramebuffers();
    texture->createTextureImage();
    texture->createTextureImageView();
    texture->createTextureSampler();
    model->loadModel();
    vertexBuffer->createVertexBuffer();
    vertexBuffer->createIndexBuffer();
    uniformBuffer->createUniformBuffers();
    descriptorSet->createDescriptorPool();
    descriptorSet->createDescriptorSets();
    buffers->createCommandBuffer();
    renderer->createSyncObjects();
}

void Application::mainLoop()
{
    while (!glfwWindowShouldClose(window->getWindow())) {
        glfwPollEvents();
        renderer->drawFrame();
    }
    vkDeviceWaitIdle(device->getDevice());
}

void Application::cleanup()
{
    swapChain->cleanupSwapChain();


    vkDestroyPipeline(device->getDevice(), pipeline->getGraphicsPipeline(), nullptr);
    vkDestroyPipelineLayout(device->getDevice(), pipeline->getPipelineLayout(), nullptr);

    vkDestroyRenderPass(device->getDevice(), pipeline->getRenderPass(), nullptr);


    for (size_t i = 0; i < buffers->MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(device->getDevice(), uniformBuffer->getUniformBuffers()[i], nullptr);
        vkFreeMemory(device->getDevice(), uniformBuffer->getUniformBuffersMemory()[i], nullptr);
    }

    vkDestroyDescriptorPool(device->getDevice(), descriptorSet->getDescriptorPool(), nullptr);

    vkDestroySampler(device->getDevice(), texture->getTextureSampler(), nullptr);
    vkDestroyImageView(device->getDevice(), texture->getTextureImageView(), nullptr);

    vkDestroyImage(device->getDevice(), texture->getTextureImage(), nullptr);
    vkFreeMemory(device->getDevice(), texture->getTextureImageMemory(), nullptr);


    vkDestroyDescriptorSetLayout(device->getDevice(), descriptorSet->getDescriptorSetLayout(), nullptr);


    vkDestroyBuffer(device->getDevice(), vertexBuffer->getIndexBuffer(), nullptr);
    vkFreeMemory(device->getDevice(), vertexBuffer->getIndexBufferMemory(), nullptr);

    vkDestroyBuffer(device->getDevice(), vertexBuffer->getVertexBuffer(), nullptr);
    vkFreeMemory(device->getDevice(), vertexBuffer->getVertexBufferMemory(), nullptr);

    for (size_t i = 0; i < buffers->MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device->getDevice(), renderer->getRenderFinishedSemaphores()[i], nullptr);
        vkDestroySemaphore(device->getDevice(), renderer->getImageAvailableSemaphores()[i], nullptr);
        vkDestroyFence(device->getDevice(), renderer->getInFlightFences()[i], nullptr);
    }

    vkDestroyCommandPool(device->getDevice(), buffers->getCommandPool(), nullptr);

    vkDestroyDevice(device->getDevice(), nullptr);

    validationManager = instance->getValidationManager();
    if (enableValidationLayers) {
        validationManager->DestroyDebugUtilsMessengerEXT(instance->getInstance(), validationManager->getDebugMessenger(), nullptr);
    }

    vkDestroySurfaceKHR(instance->getInstance(), window->getSurface(), nullptr);
    vkDestroyInstance(instance->getInstance(), nullptr);

    glfwDestroyWindow(window->getWindow());

    glfwTerminate();
}
