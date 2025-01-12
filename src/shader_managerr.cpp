#include "shader_managerr.h"

ShaderManager::ShaderManager(const std::string& vertexSource, const std::string& fragmentSource) {
    shaderProgram = Shader::CreateFromSource(vertexSource, fragmentSource);
    if (!shaderProgram) {
        std::cerr << "Failed to create initial shader program from source." << std::endl;
        return;
    }
    glUseProgram(shaderProgram->getShaderID());
}


const std::unique_ptr<Shader>& ShaderManager::getShaderProgram() const {
    return shaderProgram;
}

void ShaderManager::deleteShader() {
    if (shaderProgram) {
        shaderProgram->deleteShader();
        shaderProgram.reset();
    }
}
void ShaderManager::changeShader(const std::string& vertexSource, const std::string& fragmentSource) {
    deleteShader();
    shaderProgram = Shader::CreateFromSource(vertexSource, fragmentSource);
    if (!shaderProgram) {
        std::cerr << "Failed to create shader from source." << std::endl;
        return;
    }

    std::cout << "ShaderManager: Switched to shader program ID " << shaderProgram->getShaderID() << std::endl;
    glUseProgram(shaderProgram->getShaderID());
}

