#include "config.h"

int main() {
    GLFWwindow* window;

    if (!glfwInit()){
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Frac", NULL, NULL);
    
    return 0;
}