#pragma once

#include "config.h"
#include "glfw_manager.h"
#include "glsl_manager.h"
#include "shader_managerr.h"
#include "camera.h"
#include "camera_controller.h"
#include "scene_renderer.h"
#include <memory>
#include "mandelbulb.h"

class AppController {
public:
    AppController();
    ~AppController();

    void run();

private:
    GLFWManager glfwManager;
    GLSLManager glslManager;
    std::unique_ptr<ShaderManager> shaderManager; 
    Camera camera;
    CameraController cameraController;
    SceneRenderer* sceneRenderer;

    int resolutionX = 1920;
    int resolutionY = 1080;

    void init();
    void createShader();
    void setupScene();
    void processInput();
    bool shouldClose();
    void endFrame();
};