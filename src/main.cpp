#include "config.h"
#include "shader_manager.h"
#include "camera.h"
#include "triangle_mesh.h"



int main() {
	
	GLFWwindow* window;
	ShaderManager shaderManager;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	window = glfwCreateWindow(640, 480, "Fractalator", NULL, NULL);
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

	int projectionLocation = glGetUniformLocation(shader, "projection");
	int viewLocation = glGetUniformLocation(shader, "view");
	int cameraPosLocation = glGetUniformLocation(shader, "cameraPos");

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, camera.getProjectionMatrix().data()); //pass the projection matrix to the shader


	// MAIN RENDER LOOP

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		float time = glfwGetTime();
		camera.rotateAroundPoint(time, Eigen::Vector3f(0.0f, 0.0f, 0.0f), 3.0f);

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, camera.getViewMatrix().data()); // send viewmatrix to shader
		glUniform3f(cameraPosLocation, camera.getViewMatrix()(0, 3), camera.getViewMatrix()(1, 3), camera.getViewMatrix()(2, 3)); // send camerapos to shader

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);

	}


	glDeleteProgram(shader);
	glfwTerminate();
	return 0;


}
