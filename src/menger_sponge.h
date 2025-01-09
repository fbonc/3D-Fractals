#pragma once
#include "fractal.h"

class MengerSponge : public Fractal {
public:
    MengerSponge();
    std::string getShaderFilePath() const override;
};