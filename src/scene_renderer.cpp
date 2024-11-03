#include "scene_renderer.h"

SceneRenderer::SceneRenderer(const ShaderManager& shaderManager, const Camera& cameraInput) : shaderManager(shaderManager), camera(cameraInput), cameraController(camera)
{

	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    glUseProgram(shaderManager.getShaderProgram()->getShaderID());

}

SceneRenderer::~SceneRenderer()
{
    
}


void SceneRenderer::mainRenderLoop() {
    
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
