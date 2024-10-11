
#include "glfw_manager.h"

GLFWManager::GLFWManager() 
    :   lastX(1920.0f / 2.0f), 
        lastY(1080.0f / 2.0f), 
        firstMouse(true), 
        modeSwitchPressed(false), 
        deltaTime(0.0f), 
        lastFrame(0.0f)
{
    initialiseGLFW();
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
	
	window = glfwCreateWindow(resolutionX, resolutionY, "Fractalator", NULL, NULL);
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

	
	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
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
    if (cameraController->getMode() == CameraController::Mode::FreeCam) {
        cameraController->processMouseMovement(xoffset, yoffset);  //only process in freeCam mode
    }
}


void GLFWManager::processInput(CameraController& cameraController) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

	bool isShiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

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
    


    //switch between autoRotation and freeCam modes
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !modeSwitchPressed) {
        if (cameraController.getMode() == CameraController::Mode::AutoRotation) {
            cameraController.setMode(CameraController::Mode::FreeCam);
            std::cout << "Switched to FreeCam mode\n";
        } else {
            cameraController.setMode(CameraController::Mode::AutoRotation);
            std::cout << "Switched to AutoRotation mode\n";
        }
        modeSwitchPressed = true;  //prevent repeated toggling
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        modeSwitchPressed = false;
    }
}
