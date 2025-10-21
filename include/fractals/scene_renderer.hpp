#pragma once
#include <fractals/fractal.hpp>
#include "internal/shader_manager.hpp"
#include <fractals/camera_controller.hpp>
#include <memory>

class SceneRenderer {
public:
    SceneRenderer(const ShaderManager& shaderManager, CameraController& cameraController);
    ~SceneRenderer();

    void setFractal(std::unique_ptr<Fractal> fractal); //set active fractal
    void initialiseUniformLocations();
    void initialiseQuad();
    void startLoop();
    void endLoop();

    void setResolutionUniform(float resX, float resY);
    void setCameraPosUniform(Eigen::Vector3f cameraPos);
    void setTargetUniform(Eigen::Vector3f target);

    void setUniformValue(const std::string& name, float value);
    void setUniformValue(const std::string& name, float x, float y, float z);
    float getUniformValue(const std::string& name) const;
    Eigen::Vector3f getUniformVec3(const std::string& name) const;

    Fractal* getCurrentFractal() const;

    void setFractalUniforms();
    void setGlobalUniforms();

    std::unique_ptr<Fractal> currentFractal;

    void resetUniformBools();

private:
    bool defaultsSet = false;
    bool fractalsSet = false;

    const ShaderManager& shaderManager;
    CameraController& cameraController;
    std::unordered_map<std::string, int> uniformLocations;

    unsigned int VAO, VBO;
};
