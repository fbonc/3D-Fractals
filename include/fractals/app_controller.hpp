#pragma once

#include <fractals/glfw_manager.hpp>
#include <fractals/glsl_manager.hpp>
#include <fractals/shader_manager.hpp>
#include <fractals/camera.hpp>
#include <fractals/camera_controller.hpp>
#include <fractals/scene_renderer.hpp>
#include <fractals/ui_manager.hpp>


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