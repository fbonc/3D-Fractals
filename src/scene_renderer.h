#pragma once
#include "Fractal.h"
#include "shader_managerr.h"
#include "camera_controller.h"
#include "config.h"
#include <memory>

class SceneRenderer {
public:
    SceneRenderer(const ShaderManager& shaderManager, CameraController& cameraController);
    ~SceneRenderer();

    void setFractal(std::unique_ptr<Fractal> fractal);  // Set active fractal
    void initializeUniformLocations();
    void render();

private:
    void setCommonUniforms();
    void setFractalUniforms();

    const ShaderManager& shaderManager;
    CameraController& cameraController;
    std::unique_ptr<Fractal> currentFractal;
    std::unordered_map<std::string, int> uniformLocations;
};
