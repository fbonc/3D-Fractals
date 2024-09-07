#include "config.h"
#include "shader_manager.h"
#include "camera.h"



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
	// int w,h;
	// glfwGetFramebufferSize(window, &w, &h);
	// glViewport(0,0,w,h);


	unsigned int shader = shaderManager.make_shader(
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/vertex.vert",
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/fragment.frag"
	);

	glUseProgram(shader);

	// unsigned int shader = make_shader(
	// 	"src/shaders/vertex.vert",
	// 	"src/shaders/fragment.frag"
	// );


	Camera camera (45.0f * M_PI / 180.0f, (float)resolutionX / (float)resolutionY, 0.1f, 100.0f);

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

	float rotationSpeed = 0.5f;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float time = glfwGetTime() * rotationSpeed;


		camera.rotateAroundPoint(time, Eigen::Vector3f(0.0f, 0.0f, 0.0f), 3.0f);

		Eigen::Vector3f cameraPos = camera.getPosition();
		glUniform3f(cameraPosLocation, cameraPos.x(), cameraPos.y(), cameraPos.z());

		glUniform3f(targetLocation, 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
		glBindVertexArray(0);


		glfwSwapBuffers(window);

	}


	glDeleteProgram(shader);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;


}
