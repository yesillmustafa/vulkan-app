#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <stdexcept>

// Forward declaration of ValidationManager class
class ValidationManager;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};


#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class Instance {
public:
    Instance();

    void createInstance();
    VkInstance getInstance();
    ValidationManager* getValidationManager();
protected:
    ValidationManager* validation_manager;

private:
    VkInstance instance;
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
};

#endif
