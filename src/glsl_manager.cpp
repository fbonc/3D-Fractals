#include "glsl_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

GLSLManager::GLSLManager() {
}

GLSLManager::~GLSLManager() {
}

std::string GLSLManager::generateVertexShader() {
    std::string vertexShaderCode = readShaderFile("shaders/vertex.vert");
    return vertexShaderCode;
}

std::string GLSLManager::generateFragmentShader(const int& fractalID) {
    std::string uniformsCode = readShaderFile(universalUniformsPath);
    std::string perlinNoiseCode = readShaderFile(perlinNoisePath);
    std::string transformationsCode = readShaderFile(transformationsPath);
    std::string colouringCode = readShaderFile(colouringPath);
    std::string lightingCode = readShaderFile(lightingPath);
    std::string backgroundCode = readShaderFile(backgroundPath);
    std::string postProcessingCode = readShaderFile(postProcessingPath);
    std::string rayMarchingCode = readShaderFile(rayMarchingPath);
    std::string mainCode = readShaderFile(mainPath);

    //fractal specific code based on fractalID
    std::string fractalCode = getFractalCode(fractalID);

    //full fragment shader code
    std::ostringstream fragmentShaderStream;
    fragmentShaderStream << "#version 330 core\n\n";
    fragmentShaderStream << "out vec4 screenColor;\n\n";

    fragmentShaderStream << uniformsCode << "\n";
    fragmentShaderStream << fractalCode << "\n";
    fragmentShaderStream << perlinNoiseCode << "\n";
    fragmentShaderStream << transformationsCode << "\n";
    fragmentShaderStream << colouringCode << "\n";
    fragmentShaderStream << lightingCode << "\n";
    fragmentShaderStream << backgroundCode << "\n";
    fragmentShaderStream << postProcessingCode << "\n";
    fragmentShaderStream << rayMarchingCode << "\n";
    fragmentShaderStream << mainCode << "\n";

    //std::cout << fragmentShaderStream.str() <<std::endl;

    return fragmentShaderStream.str();
}

std::string GLSLManager::readShaderFile(const std::string& filepath) const {
    std::ifstream fileStream(filepath);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open shader file " << filepath << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

std::string GLSLManager::getFractalCode(const int& fractalID) const {

    switch (fractalID) {
        case 0:
            return readShaderFile(mandelbulbPath);
        case 1:
            return readShaderFile(mengerSpongePath);
        case 2:
            return readShaderFile(juliaPath);
        case 3:
            return readShaderFile(kleinianPath);
        case 4:
            return readShaderFile(mandelboxPath);
        default:
            std::cerr << "Error: Unknown fractalID " << fractalID << std::endl;
            return "";
    }
}
