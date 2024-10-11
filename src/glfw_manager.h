#include "config.h"
#include "camera_controller.h"


class GLFWManager
{
private:
    /* data */
    float lastX;
    float lastY;
    bool firstMouse;
    bool modeSwitchPressed;

    float deltaTime;  //time between current frame and last frame
    float lastFrame;  //time of last frame

    GLFWwindow* window;

    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow* window, CameraController& cameraController);
    int initialiseGLFW();

    
public:

    GLFWManager(/* args */);
    ~GLFWManager();
    GLFWwindow* getWindow();

};
