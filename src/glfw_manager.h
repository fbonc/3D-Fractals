#include "config.h"
#include "camera_controller.h"


class GLFWManager
{
private:

    static float lastX;
    static float lastY;
    static bool firstMouse;
    bool modeSwitchPressed;

    float deltaTime;  //time between current frame and last frame
    float lastFrame;  //time of last frame

    static GLFWwindow* window;

    static void mouseCallback(GLFWwindow*, double xpos, double ypos);
    void processInput(CameraController& cameraController);
    int initialiseGLFW();

    
public:

    void setInputFunctions(CameraController& cameraController);
    GLFWManager(/* args */);
    ~GLFWManager();
    GLFWwindow* getWindow();

};
