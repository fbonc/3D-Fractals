#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class GLSLManager {
public:
    enum class LightMode {
        PHONG,
        BLINN_PHONG,
        NONE
    };

    GLSLManager();
    ~GLSLManager();

    void setBaseShaderPath(const std::string& basePath);
    void setFragmentShaderPath(const std::string& fragmentPath);
    void setVertexShaderPath(const std::string& vertexPath);

    void setLightMode(LightMode mode);

    std::string generateVertexShader();
    std::string generateFragmentShader(const std::vector<std::string>& fractalCode);

private:
    std::string baseShaderPath;
    std::string fragmentShaderPath;
    std::string vertexShaderPath;

    LightMode currentLightMode;

    std::string getLightModeCode() const;
    std::string readShaderFile(const std::string& filepath) const;
};