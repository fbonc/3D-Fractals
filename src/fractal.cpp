#include "fractal.h"

const std::vector<std::string>& Fractal::getUniformNames() const {
    return uniformNames;
}

float Fractal::getUniformValue(const std::string& name) const {
    return uniforms.at(name);
}

void Fractal::setUniformValue(const std::string& name, float value) {
    uniforms[name] = value;
}
