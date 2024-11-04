#pragma once
#include "Fractal.h"

class Mandelbulb : public Fractal {
public:

    Mandelbulb();
    std::string getShaderFilePath() const override;

private:

    std::vector<std::string> uniformNames;

};

Mandelbulb::Mandelbulb() {
    uniformNames = {"Power", "Scale"};
    uniforms["Power"] = 8.0f;
    uniforms["Scale"] = 1.0f;
}

std::string Mandelbulb::getShaderFilePath() const {
    return "shaders/mandelbulb.frag";
}