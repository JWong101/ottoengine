#include <GLFW/glfw3.h>
#include <string>
#include <vulkan/vulkan.h>

class RenderLoop {

private:
    // Default window size
    const int WIDTH = 800;
    const int HEIGHT = 600;


    // Validation Layer stuff used to debug
    const std::vector<const std::string> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif

    GLFWwindow *window;
    VkInstance *vkInst;
    const uint32_t WIDTH = 600;
    const uint32_t HEIGHT = 400;
    bool checkValidationLayerSupport();
    
    std::vector<std::string> getRequiredExtensions(); 

    void createInstance();
    void createWindow();
    void initVulkan();
    void init();
    void mainLoop();
    void cleanup();
    void checkSupportedExtensions();
   
   
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);
public:
    void run();
 
};
