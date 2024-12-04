#include "Fractal.h"

class MengerSponge : public Fractal {
public:

    MengerSponge();
    std::string getShaderFilePath() const override;

private:

    std::vector<std::string> uniformNames;
    
};

MengerSponge::MengerSponge() {
    uniformNames = {"Power"};
    uniforms["Power"] = 8.0f;
}

std::string MengerSponge::getShaderFilePath() const {
    return "shaders/mengersponge.frag";
}