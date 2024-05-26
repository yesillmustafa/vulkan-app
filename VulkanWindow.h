#ifndef VULKANWINDOW_HPP
#define VULKANWINDOW_HPP


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Instance.h"

class VulkanWindow {
public:
	VulkanWindow(Instance* instancePtr);
	void init();
	GLFWwindow* getWindow();
	void createSurface();
	VkSurfaceKHR getSurface();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	bool getFramebufferResized();
	void setFramebufferResized(bool value);

private:
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

	Instance* instancePtr;

	GLFWwindow* window;
	VkSurfaceKHR surface;

	bool framebufferResized = false;
};

#endif // !VULKANWINDOW_HPP

