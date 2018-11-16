#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class RenderLoop {

private:
    GLFWwindow *window;
    VkInstance *vkInst;
    const uint32_t WIDTH = 600;
    const uint32_t HEIGHT = 400;
    void createWindow();
    void initVulkan();
    void init();
    void mainLoop();
    void cleanup();
    void checkSupportedExtensions();
public:
    void run();
};
