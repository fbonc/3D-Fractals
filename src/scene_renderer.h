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

    void setFractal(std::unique_ptr<Fractal> fractal); //set active fractal
    void initialiseUniformLocations();
    void startLoop();
    void endLoop();


    void setResolutionUniform(float resX, float resY);
    void setCameraPosUniform(Eigen::Vector3f cameraPos);
    void setTargetUniform(Eigen::Vector3f target);
    void initialiseQuad();


private:
    void setFractalUniforms();
    void setGlobalUniforms();

    const ShaderManager& shaderManager;
    CameraController& cameraController;
    std::unique_ptr<Fractal> currentFractal;
    std::unordered_map<std::string, int> uniformLocations;

    unsigned int VAO, VBO;
};
