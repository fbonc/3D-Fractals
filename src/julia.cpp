#include "julia.h"

Julia::Julia()
{
    uniformNames = {"juliaIterations", "juliaC1", "juliaC2", "juliaC3", "juliaC4"};

    uniforms["juliaIterations"] = 40.0f;
    uniforms["juliaC1"] = 0.32f;
    uniforms["juliaC2"] = 0.04f;
    uniforms["juliaC3"] = 0.12f;
    uniforms["juliaC4"] = -0.63f;

    // e.g. vec4(0.32, 0.04, 0.12, -0.63)

    AutoChangeConfig juliaIterationsConfig;
    juliaIterationsConfig.rate = 1.0f;
    juliaIterationsConfig.minValue = 1.001f;
    juliaIterationsConfig.maxValue = 80.0f;
    autoChangeUniforms["juliaIterations"] = juliaIterationsConfig;

    AutoChangeConfig juliaC1Config;
    juliaC1Config.rate = 0.05f;
    juliaC1Config.minValue = -1.0f;
    juliaC1Config.maxValue = 1.0f;
    autoChangeUniforms["juliaC1"] = juliaC1Config;

    AutoChangeConfig juliaC2Config;
    juliaC2Config.rate = 0.05f;
    juliaC2Config.minValue = -1.0f;
    juliaC2Config.maxValue = 1.0f;
    autoChangeUniforms["juliaC2"] = juliaC2Config;

    AutoChangeConfig juliaC3Config;
    juliaC3Config.rate = 0.05f;
    juliaC3Config.minValue = -1.0f;
    juliaC3Config.maxValue = 1.0f;
    autoChangeUniforms["juliaC3"] = juliaC3Config;

    AutoChangeConfig juliaC4Config;
    juliaC4Config.rate = 0.05f;
    juliaC4Config.minValue = -1.0f;
    juliaC4Config.maxValue = 1.0f;
    autoChangeUniforms["juliaC4"] = juliaC4Config;
}