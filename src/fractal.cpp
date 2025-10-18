#include <fractals/fractal.hpp>
#include <iostream>


const std::vector<std::string>& Fractal::getUniformNames() const {
    return uniformNames;
}

float Fractal::getUniformValue(const std::string& name) const {
    auto it = uniforms.find(name);
    if (it != uniforms.end()) {
        return it->second;
    }
    else {
        std::cerr << "Uniform '" << name << "' not found in Fractal." << std::endl;
        return 0.0f;
    }
}

void Fractal::setUniformValue(const std::string& name, float value) {
    uniforms[name] = value;
}

const std::unordered_map<std::string, AutoChangeConfig>& Fractal::getAutoChangeUniforms() const {
    return autoChangeUniforms;
}
