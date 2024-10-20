#include "scene_renderer.h"

SceneRenderer::SceneRenderer(const ShaderManager& shaderManager) : shaderManager(shaderManager)
{

}

SceneRenderer::~SceneRenderer()
{

}


void mainRenderLoop() {
    
}

void SceneRenderer::setUniformLocations(const std::vector<std::string>& uniformNames)
{
    for (size_t i = 0; i < uniformNames.size(); ++i) {
        this->uniformLocations[uniformNames[i]] = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), uniformNames[i].c_str());
    }
}

int SceneRenderer::getUniformLocation(const std::string& uniformName)
{
    auto it = uniformLocations.find(uniformName);
    if (it != uniformLocations.end()) {
        return it->second;
    }
    return -1;
}

//template function to handle different uniform types
template<typename T>
void SceneRenderer::setUniform(const std::string& uniformName, T value)
{
    int location = getUniformLocation(uniformName);
    if (location == -1) {
        std::cout << "Uniform " << uniformName << " not found!" << std::endl;
        return;
    }

    setUniformByType(location, value);
}


template<>
void SceneRenderer::setUniformByType<int>(int location, int value) {
    glUniform1i(location, value);
}

template<>
void SceneRenderer::setUniformByType<float>(int location, float value) {
    glUniform1f(location, value);
}

template<>
void SceneRenderer::setUniformByType<bool>(int location, bool value) {
    glUniform1i(location, value);
}