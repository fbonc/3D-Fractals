#pragma once
#include "fractal.h"

class Mandelbulb : public Fractal {
public:
    Mandelbulb();
    std::string getShaderFilePath() const override;
};