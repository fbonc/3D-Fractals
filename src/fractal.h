// Fractal.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct AutoChangeConfig {
    float rate;           // Units per second
    float minValue;
    float maxValue;
};

class Fractal {
public:
    
    const std::vector<std::string>& getUniformNames() const;
    float getUniformValue(const std::string& name) const;
    void setUniformValue(const std::string& name, float value);

    const std::unordered_map<std::string, AutoChangeConfig>& getAutoChangeUniforms() const;

protected:
    std::unordered_map<std::string, float> uniforms;
    std::vector<std::string> uniformNames;
    std::unordered_map<std::string, AutoChangeConfig> autoChangeUniforms;
};
