#include "mandelbulb.h"

Mandelbulb::Mandelbulb() {
    uniformNames = {"Power", "mandelbulbIterations"};
    uniforms["Power"] = 8.0f;
    uniforms["mandelbulbIterations"] = 40.0f;
    
    // Define auto-change configuration for "Power" uniform
    AutoChangeConfig powerConfig;
    powerConfig.rate = 1.0f;      // Units per second
    powerConfig.minValue = 2.0f;
    powerConfig.maxValue = 16.0f;
    autoChangeUniforms["Power"] = powerConfig;

    AutoChangeConfig mandelbulbIterationsConfig;
    mandelbulbIterationsConfig.rate = 1.0f;
    mandelbulbIterationsConfig.minValue = 10;
    mandelbulbIterationsConfig.maxValue = 100;
    autoChangeUniforms["mandelbulbIterations"] = mandelbulbIterationsConfig;
}

std::string Mandelbulb::getShaderFilePath() const {
    return "shaders/mandelbulb.frag";
}
