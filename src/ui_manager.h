#pragma once

#include "scene_renderer.h"
#include "shader_managerr.h"

#include <unordered_map>
#include <string>

class UIManager {
public:
    UIManager(SceneRenderer& sceneRenderer, ShaderManager& shaderManager, GLFWwindow* window);
    ~UIManager();

    void init();

    void render();

    void update(float deltaTime);

    void shutdown();

private:
    SceneRenderer& sceneRenderer;
    ShaderManager& shaderManager;
    GLFWwindow* window;

    struct AutoChangeSetting {
        bool enabled;
        float rate;     
        float minValue;
        float maxValue;
        float currentValue;
        bool increasing;   
    };

    std::unordered_map<std::string, AutoChangeSetting> autoChangeSettings;

    void renderRayMarchingSettings();
    void renderSceneSettings();
    void renderLightingSettings();
    void renderPostProcessingSettings();
    void renderColouringSettings();
    void renderTransformationsSettings();
    void renderFractalSettings();

    void renderAutoChangeControls(const std::string& uniformName);
};
