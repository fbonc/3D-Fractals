#include "mandelbulb.h"

Mandelbulb::Mandelbulb() {
    uniformNames = {"Power"};
    uniforms["Power"] = 8.0f;
    uniforms["mandelbulbIterations"] = 8;
    
    // Define auto-change configuration for "Power" uniform
    AutoChangeConfig powerConfig;
    powerConfig.rate = 1.0f;      // Units per second
    powerConfig.minValue = 2.0f;
    powerConfig.maxValue = 16.0f;
    autoChangeUniforms["Power"] = powerConfig;

    AutoChangeConfig mandelbulbIterationsConfig;
    mandelbulbIterationsConfig.rate = 1.0f;
    mandelbulbIterationsConfig.minValue = 10;
    mandelbulbIterationsConfig.maxValue = 60;
    autoChangeUniforms["mandelbulbIterations"] = mandelbulbIterationsConfig;
}

std::string Mandelbulb::getShaderFilePath() const {
    return "shaders/mandelbulb.frag";
}
