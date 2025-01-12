#include "klenian.h"

Klenian::Klenian()
{
    uniformNames = {"klenianIterations"};

    uniforms["klenianIterations"] = 6.0f;

    AutoChangeConfig klenianIterationsConfig;
    klenianIterationsConfig.rate = 1.0f;
    klenianIterationsConfig.minValue = 1.001f;
    klenianIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["klenianIterations"] = klenianIterationsConfig;

}