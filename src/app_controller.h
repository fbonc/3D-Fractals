#pragma once

#include "config.h"
#include "glfw_manager.h"
#include "glsl_manager.h"
#include "shader_managerr.h"
#include "camera.h"
#include "camera_controller.h"
#include "scene_renderer.h"
#include "mandelbulb.h"
#include "ui_manager.h"
#include "glsl_manager.h"
#include <memory>


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
    std::unique_ptr<SceneRenderer> sceneRenderer;
    GLSLManager glslManager;
    std::unique_ptr<UIManager> uiManager;

    int resolutionX = 1920;
    int resolutionY = 1080;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void init();
    void createShader();
    void setupScene();
    void processInput();
    bool shouldClose();
    void endFrame();
};