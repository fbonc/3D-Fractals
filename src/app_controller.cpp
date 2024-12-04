#include "camera.h"
#include "camera_controller.h"
#include "scene_renderer.h"
#include "glfw_manager.h"
#include "glsl_manager.h"
//#include "ui_manager.h"

int main() {
    GLFWManager glfwManager;
    GLSLManager glslManager;
    
    std::string fragmentShader = glslManager.generateFragmentShader(0);
    std::string vertexShader = glslManager.generateVertexShader();
    ShaderManager shaderManager(fragmentShader, vertexShader);

    Camera camera;
    CameraController cameraController(camera);
    SceneRenderer sceneRenderer(shaderManager, cameraController);
    //UIManager uiManager;


    //Setting up
    glfwManager.setInputFunctions(cameraController);
    sceneRenderer.initialiseQuad();
    sceneRenderer.initialiseUniformLocations();


}