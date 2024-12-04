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
    std::string universalUniformsPath = "shaders/uniforms.glsl";
    std::string perlinNosiePath= "shaders/perlin_noise.glsl";
    std::string transformationsPath = "shaders/transformations.glsl";
    std::string colouringPath = "shaders/colouring.glsl";
    std::string lightingPath = "shaders/lighting.glsl";
    std::string backgroundPath = "shaders/background.glsl";
    std::string postProcessingPath = "shaders/post_processing.glsl";
    std::string rayMarchingPath= "shaders/ray_marching.glsl";
    std::string mainPath = "shaders/main.glsl";

    std::string mandelbulbPath = "shaders/mandelbulb.glsl";
    std::string mengerSpongePath = "shaders/menger_sponge.glsl";

    std::string readShaderFile(const std::string& filepath) const;
    std::string getFractalCode(const int& fractalID) const;

};