#include "menger_sponge.h"

MengerSponge::MengerSponge() {
    uniformNames = {"mengerSpongeIterations"};

    uniforms["mengerSpongeIterations"] = 8.0f;
    
    AutoChangeConfig mengerSpongeIterationsConfig;
    mengerSpongeIterationsConfig.rate = 1.0f;
    mengerSpongeIterationsConfig.minValue = 1.0f;
    mengerSpongeIterationsConfig.maxValue = 20.0f;
    autoChangeUniforms["mengerSpongeIterations"] = mengerSpongeIterationsConfig;

}
