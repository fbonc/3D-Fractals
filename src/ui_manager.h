#pragma once

#include "scene_renderer.h"
#include "shader_managerr.h"
#include "glsl_manager.h"
#include "camera_controller.h"
#include "config.h"
#include "mandelbulb.h"
#include "menger_sponge.h"
#include "julia.h"
#include "kleinian.h"
#include "mandelbox.h"

#include <unordered_map>
#include <string>
#include <optional>

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
