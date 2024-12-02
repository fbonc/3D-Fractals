#include "glsl_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

GLSLManager::GLSLManager() : currentLightMode(LightMode::NONE) {}

GLSLManager::~GLSLManager() {}

void GLSLManager::setBaseShaderPath(const std::string& basePath) {
    baseShaderPath = basePath;
}

void GLSLManager::setFragmentShaderPath(const std::string& fragmentPath) {
    fragmentShaderPath = fragmentPath;
}

void GLSLManager::setVertexShaderPath(const std::string& vertexPath) {
    vertexShaderPath = vertexPath;
}

void GLSLManager::setLightMode(LightMode mode) {
    currentLightMode = mode;
}

std::string GLSLManager::generateVertexShader() {
    return readShaderFile(vertexShaderPath);
}

std::string GLSLManager::generateFragmentShader(const std::vector<std::string>& fractalCode) {
    std::ostringstream shaderStream;

    shaderStream << "#version 330 core\n\n";
    shaderStream << readShaderFile(baseShaderPath);

    shaderStream << "\n// Lighting Code\n";
    shaderStream << getLightModeCode();

    // Add fractal-specific code
    shaderStream << "\n// Fractal-Specific Code\n";
    for (const auto& line : fractalCode) {
        shaderStream << line << "\n";
    }

    return shaderStream.str();
}

std::string GLSLManager::getLightModeCode() const {
    switch (currentLightMode) {
        case LightMode::PHONG:
            return R"(
                vec3 calculatePhongLighting(vec3 normal, vec3 lightDir, vec3 viewDir) {
                    vec3 reflectDir = reflect(-lightDir, normal);
                    vec3 ambient = vec3(0.1);
                    vec3 diffuse = max(dot(normal, lightDir), 0.0) * vec3(0.5);
                    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), 32.0) * vec3(0.3);
                    return ambient + diffuse + specular;
                }
            )";
        case LightMode::BLINN_PHONG:
            return R"(
                vec3 calculateBlinnPhongLighting(vec3 normal, vec3 lightDir, vec3 viewDir) {
                    vec3 halfwayDir = normalize(lightDir + viewDir);
                    vec3 ambient = vec3(0.1);
                    vec3 diffuse = max(dot(normal, lightDir), 0.0) * vec3(0.5);
                    vec3 specular = pow(max(dot(normal, halfwayDir), 0.0), 16.0) * vec3(0.3);
                    return ambient + diffuse + specular;
                }
            )";
        case LightMode::NONE:
            return "// No lighting applied\n";
        default:
            return "// Unsupported lighting mode\n";
    }
}

std::string GLSLManager::readShaderFile(const std::string& filepath) const {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}