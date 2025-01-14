
#include "glfw_manager.h"

float GLFWManager::lastX = 1920.0f / 2.0f;
float GLFWManager::lastY = 1920.0f / 2.0f;
bool GLFWManager::firstMouse = true;
GLFWwindow* GLFWManager::window = nullptr;
bool GLFWManager::isCursorShown = false;

GLFWManager::GLFWManager() 
        :
        modeSwitchPressed(false), 
        deltaTime(0.0f), 
        lastFrame(0.0f)
{
    initialiseGLFW();
}

GLFWManager::~GLFWManager()
{
    glfwTerminate();
}


GLFWwindow* GLFWManager::getWindow() {
    return window;
}

void GLFWManager::setInputFunctions(CameraController& cameraController) {
    glfwSetWindowUserPointer(window, &cameraController);
    glfwSetCursorPosCallback(window, GLFWManager::mouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}   

int GLFWManager::initialiseGLFW() {
    const int resolutionX = 1920;
	const int resolutionY = 1080;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	window = glfwCreateWindow(resolutionX, resolutionY, "3D Fractal Generation", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GFLW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}


    return 0;
}

void GLFWManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; //reversed since y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    CameraController* cameraController = reinterpret_cast<CameraController*>(glfwGetWindowUserPointer(window));
    if (cameraController->getMode() == 1 && !isCursorShown) {
        cameraController->processMouseMovement(xoffset, yoffset);  //only process in freeCam mode
    }
}



void GLFWManager::processInput(CameraController& cameraController) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

	bool isShiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
    bool isKPressed = (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraController.processKeyboardInput(GLFW_KEY_W, deltaTime, isShiftPressed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_S, deltaTime, isShiftPressed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_A, deltaTime, isShiftPressed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_D, deltaTime, isShiftPressed);
    }
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_SPACE, deltaTime, isShiftPressed);
    }
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_LEFT_CONTROL, deltaTime, isShiftPressed);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_UP, deltaTime, isShiftPressed);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        cameraController.processKeyboardInput(GLFW_KEY_DOWN, deltaTime, isShiftPressed);
    }

    if (isKPressed && !wasKPressed) {
        if (isCursorShown) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isCursorShown = false;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isCursorShown = true;
        }
    }

    wasKPressed = isKPressed;

}



void GLFWManager::endLoop() {
    glfwSwapBuffers(window);
	glfwPollEvents();
}