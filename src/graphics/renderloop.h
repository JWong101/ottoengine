#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
class RenderLoop {

private:
    GLFWwindow *window;
    VkInstance vkInst;
    const int WIDTH = 600;
    const int HEIGHT = 400;
    void createWindow();
    void initVulkan();
    void init();
    void mainLoop();
    void cleanup();

public:
    void run();
}
