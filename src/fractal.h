// Fractal.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Fractal {
public:
    virtual ~Fractal() = default;
    
    virtual std::string getShaderFilePath() const = 0;
    const std::vector<std::string>& getUniformNames() const;
    float getUniformValue(const std::string& name) const;
    void setUniformValue(const std::string& name, float value);

protected:
    std::unordered_map<std::string, float> uniforms;
    std::vector<std::string> uniformNames;
};
