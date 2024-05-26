#include "VulkanWindow.h"

VulkanWindow::VulkanWindow(Instance* instancePtr) : instancePtr(instancePtr) {}

void VulkanWindow::init()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

GLFWwindow* VulkanWindow::getWindow()
{
    return window;
}

void VulkanWindow::createSurface()
{
    if (glfwCreateWindowSurface(instancePtr->getInstance(), window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

VkSurfaceKHR VulkanWindow::getSurface()
{
    return surface;
}

bool VulkanWindow::getFramebufferResized()
{
    return framebufferResized;
}

void VulkanWindow::setFramebufferResized(bool value)
{
    framebufferResized = value;
}

void VulkanWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto app = reinterpret_cast<VulkanWindow*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}
