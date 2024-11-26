// #include "scene_renderer.h"
// #include "mandelbulb.cpp"
// #include "shader_manager.h"
// #include "camera_controller.h"

// int main() {

//     ShaderManager shaderManager("vertex.vert", "fragment.frag");
//     Camera camera;
//     CameraController cameraController(camera);

//     SceneRenderer renderer(shaderManager, cameraController);
//     renderer.setFractal(std::make_unique<Mandelbulb>());

//     while (!glfwWindowShouldClose(window)) {
//         processInput(window, cameraController);
//         renderer.render();
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     return 0;
// }