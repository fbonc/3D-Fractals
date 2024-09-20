#include "config.h"
#include "shader_manager.h"
#include "camera.h"

//variables for tracking time, mouse position, and camera mode
float lastX = 1920.0f / 2.0f;
float lastY = 1080.0f / 2.0f;
bool firstMouse = true;
bool modeSwitchPressed = false;

float deltaTime = 0.0f;  //time between current frame and last frame
float lastFrame = 0.0f;  //time of last frame


// Mouse callback function to process mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera->getMode() == Camera::Mode::FreeCam) {
        camera->processMouseMovement(xoffset, yoffset);  // Only process in freeCam mode
    }
}

//process keyboard input for movement and switching camera modes
void processInput(GLFWwindow* window, Camera& camera) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboardInput(GLFW_KEY_W, deltaTime);
		}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.processKeyboardInput(GLFW_KEY_S, deltaTime);
		}
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.processKeyboardInput(GLFW_KEY_A, deltaTime);
		}
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.processKeyboardInput(GLFW_KEY_D, deltaTime);
		}

    //switch between autoRotation and freeCam modes
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !modeSwitchPressed) {
        if (camera.getMode() == Camera::Mode::AutoRotation) {
            camera.setMode(Camera::Mode::FreeCam);
			std::cout << "Switched to FreeCam mode\n";
        } else {
            camera.setMode(Camera::Mode::AutoRotation);
			std::cout << "Switched to AutoRotation mode\n";
        }
        modeSwitchPressed = true;  //prevent repeated toggling
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        modeSwitchPressed = false;
    }
}

int main() {
	
	GLFWwindow* window;
	ShaderManager shaderManager;

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


	// PC
	// unsigned int shader = shaderManager.make_shader(
	// 	"C:/Users/felip/Desktop/Projects/NEA/src/shaders/vertex.vert",
	// 	"C:/Users/felip/Desktop/Projects/NEA/src/shaders/fragment.frag"
	// );


	//Laptop
	unsigned int shader = shaderManager.make_shader(
		"C:/Users/felip/Desktop/dev/NEA/src/shaders/vertex.vert",
		"C:/Users/felip/Desktop/dev/NEA/src/shaders/fragment.frag"
	);

	glUseProgram(shader);


	Camera camera (45.0f * M_PI / 180.0f, (float)resolutionX / (float)resolutionY, 0.1f, 100.0f);

	//set the camera as a pointer for the mouse callback
    glfwSetWindowUserPointer(window, &camera);

    //set mouse callback function
    glfwSetCursorPosCallback(window, mouse_callback);

    //capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int cameraPosLocation = glGetUniformLocation(shader, "cameraPos");
	int targetLocation = glGetUniformLocation(shader, "target");

	int resolution = glGetUniformLocation(shader, "resolution");
	glUniform2f(resolution, resolutionX, resolutionY);


	float quadVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


	// MAIN RENDER LOOP

	float rotationSpeed = 0.1f;

	while (!glfwWindowShouldClose(window)) {
		// Process input
        processInput(window, camera);

        // Clear screen and render scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update(deltaTime, Eigen::Vector3f(0.0f, 0.0f, 0.0f));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float time = glfwGetTime() * rotationSpeed;


		Eigen::Vector3f cameraPos = camera.getPosition();
		glUniform3f(cameraPosLocation, cameraPos.x(), cameraPos.y(), cameraPos.z());

		
		//glUniform3f(targetLocation, 0.0f, 0.0f, 0.0f); //outside view
		glUniform3f(targetLocation, 0.0f, 0.0f, 0.0f); //inside view

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();

	}


	glDeleteProgram(shader);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;


}
