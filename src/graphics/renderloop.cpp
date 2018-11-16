#include "renderloop.h"
#include <optional>

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

    //check this later
    VkExtensionProperties supportedExtensions[numExtensions];
    vkEnumerateInstance(nullptr, &numSupportedExtensions, supportedExtensions);
}

void RenderLoop::initVulkan() {
    createInstance();
    VkApplicationInfo appInfo;
    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "Victoria 3";
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "OttoEngine";
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    //extensions to interact with host OS
    unsigned int extensionCount;
    const char **extensionNames;
    extensionNames = glfwGetRequiredInstanceExtensions(&extensionCount);
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensionNames;

    createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &vkInst) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vk instance\n");
    }

    
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
