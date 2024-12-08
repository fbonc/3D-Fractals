#include "mandelbulb.h"


Mandelbulb::Mandelbulb() {
    uniformNames = {"Power"};
    uniforms["Power"] = 8.0f;
}

std::string Mandelbulb::getShaderFilePath() const {
    return "shaders/mandelbulb.frag";
}