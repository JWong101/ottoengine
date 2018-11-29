#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>

#define NDEBUG

class RenderLoop {

private:
    // Default window size
    const int WIDTH = 800;
    const int HEIGHT = 600;


    // Validation Layer stuff used to debug
    const std::vector<std::string> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    GLFWwindow *window;
    VkInstance *vkInst;
    bool checkValidationLayerSupport();
    
    std::vector<std::string> getRequiredExtensions(); 

    void createInstance();
    void createWindow();
    void checkSupportedExtensions();
   
    void setupPhysicalDevice();   
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);
public:
    RenderLoop();
    ~RenderLoop();
    void init();
    void mainloop();
    void cleanup();
 
};
#endif
