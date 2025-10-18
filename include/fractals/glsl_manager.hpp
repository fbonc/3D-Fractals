#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class GLSLManager {
public:

    GLSLManager();
    ~GLSLManager();

    std::string generateVertexShader();
    std::string generateFragmentShader(const int& fractalID);

private:
    std::string universalUniformsPath = "assets/shaders/util/uniforms.glsl";
    std::string perlinNoisePath= "assets/shaders/util/perlin_noise.glsl";
    std::string transformationsPath = "assets/shaders/mods/transformations.glsl";
    std::string colouringPath = "assets/shaders/mods/colouring.glsl";
    std::string lightingPath = "assets/shaders/scene/lighting.glsl";
    std::string backgroundPath = "assets/shaders/scene/background.glsl";
    std::string postProcessingPath = "assets/shaders/scene/post_processing.glsl";
    std::string rayMarchingPath= "assets/shaders/ray_marching.glsl";
    std::string mainPath = "assets/shaders/main.glsl";

    std::string mandelbulbPath = "assets/shaders/sdf/mandelbulb.glsl";
    std::string mengerSpongePath = "assets/shaders/sdf/menger_sponge.glsl";
    std::string juliaPath = "assets/shaders/sdf/julia.glsl";
    std::string kleinianPath = "assets/shaders/sdf/kleinian.glsl";
    std::string mandelboxPath = "assets/shaders/sdf/mandelbox.glsl";

    std::string readShaderFile(const std::string& filepath) const;
    std::string getFractalCode(const int& fractalID) const;

};