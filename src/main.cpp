#include "config.h"
#include "shader_manager.h"
#include "triangle_mesh.h"



int main() {
	
	GLFWwindow* window;
	ShaderManager shaderManager;

	if (!glfwInit()) {
		return -1;
	}
	
	window = glfwCreateWindow(640, 480, "Fractalator", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}

	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
	int w,h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0,0,w,h);

	TriangleMesh* triangle = new TriangleMesh();

	unsigned int shader = shaderManager.make_shader(
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/vertex.vert",
		"C:/Users/felip/Desktop/Projects/NEA/src/shaders/fragment.frag"
	);

	// unsigned int shader = make_shader(
	// 	"src/shaders/vertex.vert",
	// 	"src/shaders/fragment.frag"
	// );

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		//triangle->draw();
		glfwSwapBuffers(window);
	}

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;

}
