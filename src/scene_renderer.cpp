// SceneRenderer.cpp
#include "scene_renderer.h"

SceneRenderer::SceneRenderer(const ShaderManager& shaderManager, CameraController& cameraController)
    : shaderManager(shaderManager), cameraController(cameraController), currentFractal(nullptr), VAO(0), VBO(0) {}

SceneRenderer::~SceneRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SceneRenderer::setFractal(std::unique_ptr<Fractal> fractal) {
    currentFractal = std::move(fractal);
    initialiseUniformLocations();
}

void SceneRenderer::initialiseQuad() {
    float quadVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void SceneRenderer::initialiseUniformLocations() {
    uniformLocations.clear();
    if (currentFractal) {
        for (const auto& name : currentFractal->getUniformNames()) {
            int location = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), name.c_str());
            if (location != -1) {
                uniformLocations[name] = location;
            }
        }
    }

    std::vector<std::string> globalUniforms = {
    "cameraPos", "target", "resolution",
    "MAX_DIST", "MAX_STEPS", "EPSILON", "repeatFractal", "repeatCellSize",
    "backgroundColour", "useHalo", "useGradient", "haloRadius", "haloColour", "fractalColour",
    "ambientColor", "lightSourceDir", "specularStrength", "shininess", "ambientOcclusion", 
    "softShadows", "shadowMaxSteps", "kSoftShadow", "lightestShadow", "darkestShadow",
    "glowOn", "glowColor", "glowStrength",
    "gammaAmount", "contrastAmount", "saturationAmount", "vignetteAmount", "luminanceColour",
    "colorMode", "positionColouringScale", "positionColourOne", "positionColourTwo",
    "iterationColourVarOne", "iterationColourVarTwo", "iterationColourVarThree", "iterationColourVarFour",
    "useScale", "scaleAmount", "useTwist", "twistAmount", "useBend", "bendAmount", "useWarp", "warpAmount"
    };

    for (const auto& uniformName : globalUniforms) {
        int loc = glGetUniformLocation(shaderManager.getShaderProgram()->getShaderID(), uniformName.c_str());
        if (loc != -1) {
            uniformLocations[uniformName] = loc;
        } else {
            std::cout << "Global Uniform '" << uniformName << "' not found in shader." << std::endl;
        }
    }

    setGlobalUniforms();
}

void SceneRenderer::setResolutionUniform(float resX, float resY) {
    glUniform2f(uniformLocations["resolution"], resX, resY);
}

void SceneRenderer::setCameraPosUniform(Eigen::Vector3f cameraPos) {
    glUniform3f(uniformLocations["cameraPos"], cameraPos.x(), cameraPos.y(), cameraPos.z());
}


void SceneRenderer::setTargetUniform(Eigen::Vector3f target) {
    auto it = uniformLocations.find("target");
    if (it != uniformLocations.end()) {
        glUniform3f(it->second, target.x(), target.y(), target.z());
    }
    else {
        std::cerr << "Uniform 'target' not found." << std::endl;
    }
}

void SceneRenderer::setGlobalUniforms() {
    glUseProgram(shaderManager.getShaderProgram()->getShaderID());

    auto setUniform1f = [&](const std::string &name, float val) {
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end()) {
            glUniform1f(it->second, val);
        }
    };

    auto setUniform1i = [&](const std::string &name, int val) {
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end()) {
            glUniform1i(it->second, val);
        }
    };

    auto setUniform3f = [&](const std::string &name, float x, float y, float z) {
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end()) {
            glUniform3f(it->second, x, y, z);
        }
    };

    setUniform1f("MAX_DIST", 200.0f);
    setUniform1i("MAX_STEPS", 200);
    setUniform1f("EPSILON", 0.001f);
    setUniform1i("repeatFractal", 0); //false
    setUniform1f("repeatCellSize", 6.7f);

    setUniform3f("backgroundColour", 0.4f, 1.0f, 1.0f);
    setUniform1i("useHalo", 1); // true
    setUniform1i("useGradient", 1); // true
    setUniform1f("haloRadius", 17.0f);
    setUniform3f("haloColour", 1.0f, 0.8f, 0.4f);
    setUniform3f("fractalColour", 0.7f, 0.7f, 0.7f);

    setUniform3f("ambientColor", 0.9137f, 0.9137f, 0.9137f);
    setUniform3f("lightSourceDir", 1.0f, 1.0f, 1.0f);
    setUniform1f("specularStrength", 0.5f);
    setUniform1f("shininess", 32.0f);

    setUniform1i("ambientOcclusion", 1); // true
    setUniform1i("softShadows", 1); // true
    setUniform1i("shadowMaxSteps", 100);
    setUniform1f("kSoftShadow", 8.0f);
    setUniform1f("lightestShadow", 0.7f);
    setUniform1f("darkestShadow", 0.2f);

    setUniform1i("glowOn", 0); // false
    setUniform3f("glowColor", 1.0f, 0.0f, 0.0f);
    setUniform1f("glowStrength", 0.5f);

    setUniform1f("gammaAmount", 2.2f);
    setUniform1f("contrastAmount", 0.5f);
    setUniform1f("saturationAmount", 1.0f);
    setUniform1f("vignetteAmount", 0.5f);
    setUniform3f("luminanceColour", 0.2126f, 0.7152f, 0.0722f);

    setUniform1i("colorMode", 3);
    setUniform1f("positionColouringScale", 0.6f);
    setUniform3f("positionColourOne", 0.0f, 1.0f, 0.6667f);
    setUniform3f("positionColourTwo", 0.149f, 0.0196f, 0.3882f);

    setUniform1f("iterationColourVarOne", 0.4f);
    setUniform1f("iterationColourVarTwo", 2.0f);
    setUniform1f("iterationColourVarThree", 3.7f);
    setUniform3f("iterationColourVarFour", 0.4118f, 0.6588f, 0.702f);

    setUniform1i("useScale", 0); // false
    setUniform1f("scaleAmount", 2.0f);
    setUniform1i("useTwist", 0); // false
    setUniform1f("twistAmount", 0.5f);
    setUniform1i("useBend", 0); // false
    setUniform1f("bendAmount", 0.1f);
    setUniform1i("useWarp", 0); // false
    setUniform1f("warpAmount", 0.0001f);
}

void SceneRenderer::setFractalUniforms() {
    if (!currentFractal) return;
    
    for (const auto& name : currentFractal->getUniformNames()) {
        float value = currentFractal->getUniformValue(name);
        auto it = uniformLocations.find(name);
        if (it != uniformLocations.end()) {
            glUniform1f(it->second, value);
        } else {
            std::cerr << "Uniform '" << name << "' not found for fractal." << std::endl;
        }
    }
}

void SceneRenderer::setUniformValue(const std::string& name, float value)
{
    auto it = uniformLocations.find(name);
    if (it != uniformLocations.end()) {
        glUniform1f(it->second, value);
    } else {
        std::cerr << "Uniform '" << name << "' not found." << std::endl;
    }
}

void SceneRenderer::setUniformValue(const std::string& name, float x, float y, float z)
{
    auto it = uniformLocations.find(name);
    if (it != uniformLocations.end()) {
        glUniform3f(it->second, x, y, z);
    } else {
        std::cerr << "Uniform '" << name << "' not found." << std::endl;
    }
}

// Getter methods for uniforms
float SceneRenderer::getUniformValue(const std::string& name) const
{
    glUseProgram(shaderManager.getShaderProgram()->getShaderID());

    auto it = uniformLocations.find(name);
    if (it != uniformLocations.end()) {
        int location = it->second;
        float value;
        glGetUniformfv(shaderManager.getShaderProgram()->getShaderID(), location, &value);
        return value;
    } else {
        std::cerr << "Uniform '" << name << "' not found." << std::endl;
        return 0.0f;
    }
}

Eigen::Vector3f SceneRenderer::getUniformVec3(const std::string& name) const
{
    glUseProgram(shaderManager.getShaderProgram()->getShaderID());

    auto it = uniformLocations.find(name);
    if (it != uniformLocations.end()) {
        int location = it->second;
        float values[3];
        glGetUniformfv(shaderManager.getShaderProgram()->getShaderID(), location, values);
        return Eigen::Vector3f(values[0], values[1], values[2]);
    } else {
        std::cerr << "Uniform '" << name << "' not found." << std::endl;
        return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }
}

// Get current fractal
Fractal* SceneRenderer::getCurrentFractal() const
{
    return currentFractal.get();
}

void SceneRenderer::startLoop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setFractalUniforms();
}

void SceneRenderer::endLoop() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glBindVertexArray(0);
}
