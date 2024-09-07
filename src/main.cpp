#include "config.h"
#include "shader_manager.h"
#include "camera.h"
//#include "triangle_mesh.h"



int main() {
	
	GLFWwindow* window;
	ShaderManager shaderManager;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	window = glfwCreateWindow(1920, 1080, "Fractalator", NULL, NULL);
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
	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0,0,w,h);


	//TriangleMesh* triangle = new TriangleMesh();

	unsigned int shader = shaderManager.make_shader(
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/vertex.vert",
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/fragment.frag"
	);

	glUseProgram(shader);

	// unsigned int shader = make_shader(
	// 	"src/shaders/vertex.vert",
	// 	"src/shaders/fragment.frag"
	// );

	// while (!glfwWindowShouldClose(window)) {
	// 	glfwPollEvents();

	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	glUseProgram(shader);
	// 	//triangle->draw();
	// 	glfwSwapBuffers(window);
	// }

	// glDeleteProgram(shader);
	// glfwTerminate();
	// return 0;

	Camera camera (45.0f * M_PI / 180.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	int cameraPosLocation = glGetUniformLocation(shader, "cameraPos");


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
	float angle = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		float deltaTime = 0.01f;
		angle += deltaTime * rotationSpeed;

		if (angle > 2.0f * M_PI) {
			angle -= 2.0f * M_PI;
		}


		camera.rotateAroundPoint(angle, Eigen::Vector3f(0.0f, 0.0f, 0.0f), 3.0f);

		Eigen::Vector3f cameraPos = camera.getPosition();

		glUniform3f(cameraPosLocation, cameraPos.x(), cameraPos.y(), cameraPos.z());

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


		glfwSwapBuffers(window);

	}


	glDeleteProgram(shader);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;


}
