// SceneRenderer.cpp
#include "scene_renderer.h"

SceneRenderer::SceneRenderer(const ShaderManager& shaderManager, CameraController& cameraController)
    : shaderManager(shaderManager), cameraController(cameraController) {}

SceneRenderer::~SceneRenderer() {}

void SceneRenderer::setFractal(std::unique_ptr<Fractal> fractal) {
    currentFractal = std::move(fractal);
    initialiseUniformLocations();
}

void SceneRenderer::initialiseQuad() {
    float quadVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void SceneRenderer::initialiseUniformLocations() {
    uniformLocations.clear();
    if (currentFractal) {
        for (const auto& name : currentFractal->getUniformNames()) {
            int location = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), name.c_str());
            if (location != -1) {
                uniformLocations[name] = location;
            }
        }
    }

    uniformLocations["cameraPos"] = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), "cameraPos");
    uniformLocations["target"] = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), "target");
    uniformLocations["resolution"] = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), "resolution");
}

void SceneRenderer::setResolutionUniform(float resX, float resY) {
        glUniform2f(uniformLocations["resolution"], resX, resY);
}

void SceneRenderer::setCameraPosUniform(Eigen::Vector3f cameraPos) {
    glUniform3f(uniformLocations["cameraPos"], cameraPos.x(), cameraPos.y(), cameraPos.z());
}


void SceneRenderer::setTargetUniform(Eigen::Vector3f target) {
    glUniform3f(uniformLocations["target"], target.x(), target.y(), target.z());
}

void SceneRenderer::setFractalUniforms() {
    if (!currentFractal) return;
    
    for (const auto& name : currentFractal->getUniformNames()) {
        int location = uniformLocations[name];
        float value = currentFractal->getUniformValue(name);
        glUniform1f(location, value);
    }
}

void SceneRenderer::startLoop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setFractalUniforms();
}

void SceneRenderer::endLoop() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
