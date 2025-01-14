#include "kleinian.h"

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