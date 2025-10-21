#pragma once

#include <fractals/scene_renderer.hpp>
#include "internal/shader_manager.hpp"
#include <fractals/glsl_manager.hpp>
#include <fractals/camera_controller.hpp>
#include <fractals/fractals.hpp>




struct AutoChangeSetting {
    bool enabled;
    float rate;
    float minValue;
    float maxValue;
    float currentValue;
    bool increasing;
};

class UIManager {
public:
    UIManager(SceneRenderer& sceneRenderer, ShaderManager& shaderManager, GLFWwindow* window, GLSLManager& glslManager, CameraController& cameraController);
    ~UIManager();

    void init();

    void initRender();
    void mainRender();

    void update(float deltaTime);

    void shutdown();

private:
    SceneRenderer& sceneRenderer;
    ShaderManager& shaderManager;
    GLFWwindow* window;
    GLSLManager& glslManager;
    CameraController& cameraController;

    std::unordered_map<std::string, AutoChangeSetting> autoChangeSettings;

    void renderRayMarchingSettings();
    void renderSceneSettings();
    void renderLightingSettings();
    void renderPostProcessingSettings();
    void renderColouringSettings();
    void renderTransformationsSettings();
    void renderFractalSettings();
    void renderCameraSettings();
    void renderAutoChangeControls(const std::string& uniformName);

    void initializeAutoChangeSettings();
    void cleanupAutoChangeSettings();
};
