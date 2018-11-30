#ifndef RENDERLOOP_H_
#define RENDERLOOP_H_

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

#define NDEBUG


class RenderLoop {

private:
    // Default window size
    const int WIDTH = 800;
    const int HEIGHT = 600;

    GLFWwindow *window;
    VkInstance *vkInst;
    VkDevice *device;

    std::unordered_map<std::string, int> queueFamilyIndices;
    // Validation Layer stuff used to debug
    const std::vector<std::string> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    void findQueueFamilies(const VkPhysicalDevice &device);
    bool isDeviceSuitable(const VkPhysicalDevice &device);
    bool checkValidationLayerSupport();
    uint32_t rateDevice(const VkPhysicalDevice &device);

    void setupApplicationInfo(VkApplicationInfo &appInfo);
    void setupCreationInfo(VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo);
    
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
