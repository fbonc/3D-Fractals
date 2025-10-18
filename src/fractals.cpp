#include <fractals/fractals.hpp>

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


Kleinian::Kleinian()
{
    uniformNames = {"kleinianIterations"};

    uniforms["kleinianIterations"] = 6.0f;

    AutoChangeConfig kleinianIterationsConfig;
    kleinianIterationsConfig.rate = 1.0f;
    kleinianIterationsConfig.minValue = 1.001f;
    kleinianIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["kleinianIterations"] = kleinianIterationsConfig;

}



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



Mandelbulb::Mandelbulb() {
    uniformNames = {"Power", "mandelbulbIterations"};
    uniforms["Power"] = 8.0f;
    uniforms["mandelbulbIterations"] = 40.0f;
    
    // Define auto-change configuration for "Power" uniform
    AutoChangeConfig powerConfig;
    powerConfig.rate = 1.0f;      // Units per second
    powerConfig.minValue = 1.0f;
    powerConfig.maxValue = 20.0f;
    autoChangeUniforms["Power"] = powerConfig;

    AutoChangeConfig mandelbulbIterationsConfig;
    mandelbulbIterationsConfig.rate = 1.0f;
    mandelbulbIterationsConfig.minValue = 1.001f;
    mandelbulbIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["mandelbulbIterations"] = mandelbulbIterationsConfig;
}




MengerSponge::MengerSponge() {
    uniformNames = {"mengerSpongeIterations"};
    uniforms["mengerSpongeIterations"] = 8.0f;
    
    AutoChangeConfig mengerSpongeIterationsConfig;
    mengerSpongeIterationsConfig.rate = 1.0f;
    mengerSpongeIterationsConfig.minValue = 1.0f;
    mengerSpongeIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["mengerSpongeIterations"] = mengerSpongeIterationsConfig;

}

