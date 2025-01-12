#include "mandelbox.h"

Mandelbox::Mandelbox()
{
    uniformNames = {"mandelboxIterations", "foldingLimit", "minRadius2", "fixedRadius2", "mbScale"};

    uniforms["mandelboxIterations"] = 10.0f;
    uniforms["foldingLimit"] = 0.611f;
    uniforms["minRadius2"] = -0.714f;
    uniforms["fixedRadius2"] = 1.169f;
    uniforms["mbScale"] = -1.815f;

    AutoChangeConfig mandelboxIterationsConfig;
    mandelboxIterationsConfig.rate = 1.0f;
    mandelboxIterationsConfig.minValue = 1.001f;
    mandelboxIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["mandelboxIterations"] = mandelboxIterationsConfig;

    AutoChangeConfig foldingLimitConfig;
    foldingLimitConfig.rate = 0.05f;
    foldingLimitConfig.minValue = -3.0f;
    foldingLimitConfig.maxValue = 3.0f;
    autoChangeUniforms["foldingLimit"] = foldingLimitConfig;

    AutoChangeConfig minRadius2Config;
    minRadius2Config.rate = 0.05f;
    minRadius2Config.minValue = -3.0f;
    minRadius2Config.maxValue = 3.0f;
    autoChangeUniforms["minRadius2"] = minRadius2Config;

    AutoChangeConfig fixedRadius2Config;
    fixedRadius2Config.rate = 0.05f;
    fixedRadius2Config.minValue = -3.0f;
    fixedRadius2Config.maxValue = 3.0f;
    autoChangeUniforms["fixedRadius2"] = fixedRadius2Config;

    AutoChangeConfig mbScaleConfig;
    mbScaleConfig.rate = 0.05f;
    mbScaleConfig.minValue = -3.0f;
    mbScaleConfig.maxValue = 3.0f;
    autoChangeUniforms["mbScale"] = mbScaleConfig;

}