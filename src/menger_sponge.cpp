#include "Fractal.h"

class MengerSponge : public Fractal {
public:

    MengerSponge();
    std::string getShaderFilePath() const override;

private:

    std::vector<std::string> uniformNames;
    
};

MengerSponge::MengerSponge() {
    uniformNames = {"Power", "Scale"};
    uniforms["Power"] = 8.0f;
    uniforms["Scale"] = 1.0f;
}

std::string MengerSponge::getShaderFilePath() const {
    return "shaders/mengersponge.frag";
}