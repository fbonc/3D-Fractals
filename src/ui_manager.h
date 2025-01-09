#pragma once

#include "scene_renderer.h"
#include "shader_managerr.h"
#include "config.h"
#include "glsl_manager.h"

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
    UIManager(SceneRenderer& sceneRenderer, ShaderManager& shaderManager, GLFWwindow* window, GLSLManager& glslManager);
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

    std::unordered_map<std::string, AutoChangeSetting> autoChangeSettings;

    void renderRayMarchingSettings();
    void renderSceneSettings();
    void renderLightingSettings();
    void renderPostProcessingSettings();
    void renderColouringSettings();
    void renderTransformationsSettings();
    void renderFractalSettings();
    void renderAutoChangeControls(const std::string& uniformName);

    void initializeAutoChangeSettings();
    void cleanupAutoChangeSettings();
};
