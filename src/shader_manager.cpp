#include <fractals/shader_manager.hpp>
#include <glad.h>
#include <iostream>
#include <stdexcept>

ShaderManager::ShaderManager(const std::string& vertexSource, const std::string& fragmentSource) {
    shaderProgram = Shader::CreateFromSource(vertexSource, fragmentSource);
    if (!shaderProgram) {
        throw std::runtime_error("Failed to create initial shader program from source");
    }
    glUseProgram(shaderProgram->getShaderID());
}

const std::unique_ptr<Shader>& ShaderManager::getShaderProgram() const { return shaderProgram; }

void ShaderManager::deleteShader() {
    if (shaderProgram) {
        shaderProgram->deleteShader();
        shaderProgram.reset();
    }
}
void ShaderManager::changeShader(const std::string& vertexSource,
                                 const std::string& fragmentSource) {
    deleteShader();
    shaderProgram = Shader::CreateFromSource(vertexSource, fragmentSource);
    if (!shaderProgram) {
        throw std::runtime_error("Failed to create shader from source");
    }

    glUseProgram(shaderProgram->getShaderID());
}
