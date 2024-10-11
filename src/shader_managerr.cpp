#include "shader_managerr.h"

ShaderManager::ShaderManager(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    shaderProgram = createShader(vertex_filepath, fragment_filepath);
}

ShaderManager::~ShaderManager() {
    deleteShader();
}

std::unique_ptr<Shader> ShaderManager::createShader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    return std::make_unique<Shader>(vertex_filepath, fragment_filepath);
}

void ShaderManager::deleteShader() {
    if (shaderProgram) {
        shaderProgram.reset();
    }
}
void ShaderManager::changeShader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    deleteShader();
    shaderProgram = createShader(vertex_filepath, fragment_filepath);
}