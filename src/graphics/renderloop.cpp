#include "renderloop.h"

void RenderLoop::createWindow() {
    glfwInit(); 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZEABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "OTTOEngine", nullptr, nullptr;
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
    const char **extensions;
    extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;

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
