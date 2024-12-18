#include "app_controller.h"

int main() {
    AppController app;
    app.run();

    return 0;
}



// #include "config.h"
// #include "shader_manager.h"
// #include "camera_controller.h"

// //variables for tracking time, mouse position, and camera mode
// float lastX = 1920.0f / 2.0f;
// float lastY = 1080.0f / 2.0f;
// bool firstMouse = true;
// bool modeSwitchPressed = false;

// float deltaTime = 0.0f;  //time between current frame and last frame
// float lastFrame = 0.0f;  //time of last frame


// //process mouse movement
// void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     if (firstMouse) {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; //reversed since y-coordinates range from bottom to top

//     lastX = xpos;
//     lastY = ypos;

//     CameraController* cameraController = reinterpret_cast<CameraController*>(glfwGetWindowUserPointer(window));
//     if (cameraController->getMode() == CameraController::Mode::FreeCam) {
//         cameraController->processMouseMovement(xoffset, yoffset);  //only process in freeCam mode
//     }
// }

// //process keyboard input for movement and switching camera modes
// void processInput(GLFWwindow* window, CameraController& cameraController, int cmLocation) {
//     float currentFrame = glfwGetTime();
//     deltaTime = currentFrame - lastFrame;
//     lastFrame = currentFrame;

// 	bool isShiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

//     if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//         cameraController.processKeyboardInput(GLFW_KEY_W, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_S, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_A, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_D, deltaTime, isShiftPressed);
//     }
// 	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_SPACE, deltaTime, isShiftPressed);
//     }
// 	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_LEFT_CONTROL, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_UP, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_DOWN, deltaTime, isShiftPressed);
//     }
//     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
//         cameraController.processKeyboardInput(GLFW_KEY_DOWN, deltaTime, isShiftPressed);
//     }


//     if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
//         glUniform1i(cmLocation, 1);
//     }
//     if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
//         glUniform1i(cmLocation, 2);
//     }
//     if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
//         glUniform1i(cmLocation, 3);
//     }
//     if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS){
//         glUniform1i(cmLocation, 4);
//     }
//     if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS){
//         glUniform1i(cmLocation, 5);
//     }
//     if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS){
//         glUniform1i(cmLocation, 6);
//     }
    
    


//     //switch between autoRotation and freeCam modes
//     if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !modeSwitchPressed) {
//         if (cameraController.getMode() == CameraController::Mode::AutoRotation) {
//             cameraController.setMode(CameraController::Mode::FreeCam);
//             std::cout << "Switched to FreeCam mode\n";
//         } else {
//             cameraController.setMode(CameraController::Mode::AutoRotation);
//             std::cout << "Switched to AutoRotation mode\n";
//         }
//         modeSwitchPressed = true;  //prevent repeated toggling
//     }

//     if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
//         modeSwitchPressed = false;
//     }
// }

// #include <filesystem>

// int main() {

//     // dogshit workaround to fix the relative file paths - cwd not working in launch.json, no idea why, tried everything
//     std::filesystem::current_path("C:/Users/felip/Desktop/Projects/NEA");
//     std::cout << "Updated working directory: " 
//               << std::filesystem::current_path() 
//               << std::endl;


//     std::cout << "Current working directory: " 
//             << std::filesystem::current_path() 
//             << std::endl;



	
// 	GLFWwindow* window;
// 	ShaderManager shaderManager;

// 	const int resolutionX = 1920;
// 	const int resolutionY = 1080;

// 	if (!glfwInit()) {
// 		std::cout << "Failed to initialize GLFW" << std::endl;
// 		return -1;
// 	}
	
// 	window = glfwCreateWindow(resolutionX, resolutionY, "Fractalator", NULL, NULL);
// 	if (!window) {
// 		std::cout << "Failed to create GFLW window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}

// 	glfwMakeContextCurrent(window);

// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// 		std::cout << "Failed to load opengl" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}

	
// 	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

// 	//load shaders
// 	unsigned int shader = shaderManager.make_shader(

//         "shaders/vertex.vert",
//         "shaders/fragment2.frag"

// 	);

// 	glUseProgram(shader);
    
// 	Camera camera;
// 	CameraController cameraController(camera);

// 	//set the cameraController as the window user pointer for mouse callbacks
//     glfwSetWindowUserPointer(window, &cameraController);

//     glfwSetCursorPosCallback(window, mouse_callback);

//     //capture the mouse
//     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

// 	int cameraPosLocation = glGetUniformLocation(shader, "cameraPos");
// 	int targetLocation = glGetUniformLocation(shader, "target");
//     int powerLocation = glGetUniformLocation(shader, "Power");
// 	int resolution = glGetUniformLocation(shader, "resolution");
//     int colorModeLocation = glGetUniformLocation(shader, "colorMode");
    
// 	glUniform2f(resolution, resolutionX, resolutionY);

// 	//vertex data for a quad (for ray marching)
// 	float quadVertices[] = {
//         -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//         -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
//          1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//         -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//          1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
//          1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f
//     };

//     unsigned int VAO, VBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

// 	//MAIN RENDER LOOP
// 	float rotationSpeed = 0.1f;
//     float power = 8.0f;
//     bool powerUp = true;
//     float powerRate = 0.015f;
// 	Eigen::Vector3f target;

//     glUniform1f(powerLocation, power);
//     glUniform1i(colorModeLocation, 1);

// 	while (!glfwWindowShouldClose(window)) {
//         processInput(window, cameraController, colorModeLocation);

//         //clear screen and render scene
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         cameraController.updateRotation(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
// 		cameraController.updateCameraVectors();


// 		//update camera uniform
// 		Eigen::Vector3f cameraPos = camera.getPosition();
// 		glUniform3f(cameraPosLocation, cameraPos.x(), cameraPos.y(), cameraPos.z());


// 		if (cameraController.getMode() == CameraController::Mode::AutoRotation) {
// 			target.x() = 0.0f; target.z() = 0.0f; target.y() = 0.0f;
// 		} else {
// 			target = cameraPos + camera.getFront();
// 		}


// 		glUniform3f(targetLocation, target.x(), target.y(), target.z()); //inside view

// 		glBindVertexArray(VAO);
// 		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
// 		glBindVertexArray(0);

// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}

// 	glDeleteProgram(shader);
// 	glDeleteVertexArrays(1, &VAO);
// 	glDeleteBuffers(1, &VBO);
// 	glfwTerminate();
// 	return 0;
// }