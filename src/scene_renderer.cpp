// SceneRenderer.cpp
#include "scene_renderer.h"

SceneRenderer::SceneRenderer(const ShaderManager& shaderManager, CameraController& cameraController)
    : shaderManager(shaderManager), cameraController(cameraController) {}

SceneRenderer::~SceneRenderer() {}

void SceneRenderer::setFractal(std::unique_ptr<Fractal> fractal) {
    currentFractal = std::move(fractal);
    initializeUniformLocations();
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

void SceneRenderer::initializeUniformLocations() {
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

void SceneRenderer::setCommonUniforms() {

    Eigen::Vector3f cameraPos = cameraController.getCamera().getPosition();
    glUniform3f(uniformLocations["cameraPos"], cameraPos.x(), cameraPos.y(), cameraPos.z());

    Eigen::Vector3f target = cameraController.getCamera().getFront() + cameraPos;
    glUniform3f(uniformLocations["target"], target.x(), target.y(), target.z());

    glUniform2f(uniformLocations["resolution"], 1920.0f, 1080.0f);
}

void SceneRenderer::setFractalUniforms() {
    if (!currentFractal) return;
    
    for (const auto& name : currentFractal->getUniformNames()) {
        int location = uniformLocations[name];
        float value = currentFractal->getUniformValue(name);
        glUniform1f(location, value);
    }
}

void SceneRenderer::render() {
    setCommonUniforms();
    setFractalUniforms();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}
