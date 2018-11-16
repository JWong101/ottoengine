#include "renderloop.h"
#include <optional>
#include <vector>
#include <unordered_set>




// Debug code, Validation layers, checking what there are
bool RenderLoop::checkValidationLayerSupport() {
    
    // get the avalable inctance layers
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


    // check to make sure all validation layers are in availableLayers i.e. make sure we have all the validation layers we claim to be using
    // we do this by storing all acutall layer properties in a set and check if ours exist in them

    std::unordered_set<std::string> availableLayerNames;
    
    for (const auto &layerProperties : availableLayers)) {
        availableLayerNames.emplace(layerProperties.layerName);
    }
    
    for (const std::string layerName : validationLayers) {
        // if the layerName is inside we can maintain truth, otherwise we return false, otherwise keep checking
        if (!availableLayerNames.count()) {
            return false;
        }
    }
    return true;
}

// gets a vector of all the GLFW extentions
std::vector<std::string> RenderLoop::getRequiredExtensions() {
    uint32_t glfwExtentionCount = 0;
    const char **glfwExtentionsBasic = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    // TODO:  make sure this works, prob wont automaticly convert char * to strings
    const std::vector<std::string> glfwExtentions {glfwExtentionsBasic, glfwExtentionsBasic + glfwExtensionCount};

    if (enableValidationLayers) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    return glfwExtentions;
}

// TODO: im pretty sure there needs to be more here
void RenderLoop::createInstance() {

    // check for validation layer support and if validation layers is enabled   
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    // search for supported extentions

    // get the number of extentions, make a vector of that length, then get and save them in that vector
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Victoria 3"; //TODO: simplify later
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "OttoEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    //extensions to interact with host OS
    uint32_t extensionCount;
    const char **extensionNames;
    extensionNames = glfwGetRequiredInstanceExtensions(&extensionCount);
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensionNames;

    createInfo.enabledLayerCount = 0;

    //TODO: disparity in code above and code bellow, determine what we want to use

    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // create VKInstance
    if(vkCreateInstance(&createInfo, nullptr, &vkInst) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vk instance\n");
    }

    // print out the avalable extentions
    std::cout << "available extensions:" << std::endl;

    for (const auto& extension : extensions) {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
}

static VKAPI_ATTR VkBool32 VKAPI_CALL RenderLoop::debugCallback (
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
    
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    
    
    return VK_FALSE;
}

void RenderLoop::createWindow() {
    glfwInit(); 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZEABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "OTTOEngine", nullptr, nullptr);
}

uint32_t rateDevice(const VkPhysicalDevice &device) {
    //can't do shit without a shader
    if(!device.geometryShader) {
        return 0;
    }

    uint32_t score = device.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ? 1000 : 0;
    score += device.limits.maxImageDimension2D;
    return score;
}

void Renderloop::setupPhysicalDevice() {
    uint32_t numDevices = 0;
    vkEnumeratePhysicalDevices(vkInst, &numDevices, nullptr);
    if(numDevices == 0) {
        throw std::runtime_error("You have a garbage computer/OS; please rethink life.\n");
    }

    VkPhysicalDevice devices[numDevices];
    vkEnumeratePhysicalDevices(vkInst, &numDevices, devices);
    uint32_t maxScore = -1;
    VkPhysicalDevice physDevice;
    for(const auto& dev : devices) {
        uint32_t score = rateDevice(&dev); 
        if(score > maxScore) {
            maxScore = score;
            physDevice = dev;
        }
    }
}

void Renderloop::checkSupportedExtensions() {
    uint32_t numSupportedExtensions = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &numExtensions, nullptr);

    // TODO: check this later
    VkExtensionProperties supportedExtensions[numExtensions];
    vkEnumerateInstance(nullptr, &numSupportedExtensions, supportedExtensions);
}

void RenderLoop::initVulkan() {
    
    createInstance();
    

    // select a supported VkPhysicalDevice
    setupPhysicalDevice()

    // create a VkDevice and a VkQueue


    // create a window and a swap chain(? idk whats handled by GLFW)

    // create a render pass that specifies the render targets and usage

    // Create framebuffers for the render pass

    // Set up the graphics pipeline (VkPipeline)

    // more stuff   
}

void RenderLoop::mainloop() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void RenderLoop::cleanup() {
    vkDestroyInstance(vkInst, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}
