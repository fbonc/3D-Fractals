#include "ui_manager.h"

UIManager::UIManager(SceneRenderer& sceneRenderer, ShaderManager& shaderManager, GLFWwindow* window, GLSLManager& glslManager)
    : sceneRenderer(sceneRenderer), shaderManager(shaderManager), window(window), glslManager(glslManager)
{
}

UIManager::~UIManager()
{
    shutdown();
}

void UIManager::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.IniFilename = nullptr;
    
    ImGui::StyleColorsClassic();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    initializeAutoChangeSettings();
}

void UIManager::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::initializeAutoChangeSettings()
{
    auto fractal = sceneRenderer.getCurrentFractal();
    if (fractal) {
        const auto& fractalAutoChange = fractal->getAutoChangeUniforms();
        for (const auto& [name, config] : fractalAutoChange) {
            AutoChangeSetting setting;
            setting.enabled = false;
            setting.rate = config.rate;
            setting.minValue = config.minValue;
            setting.maxValue = config.maxValue;
            setting.currentValue = sceneRenderer.getUniformValue(name);
            setting.increasing = true;
            autoChangeSettings[name] = setting;
        }
    }
}

void UIManager::cleanupAutoChangeSettings()
{
    auto fractal = sceneRenderer.getCurrentFractal();
    if (fractal) {
        const auto& fractalAutoChange = fractal->getAutoChangeUniforms();
        //remove settings not in fractalAutoChange
        for (auto it = autoChangeSettings.begin(); it != autoChangeSettings.end(); ) {
            if (fractalAutoChange.find(it->first) == fractalAutoChange.end()) {
                it = autoChangeSettings.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void UIManager::initRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIManager::mainRender() 
{
    renderRayMarchingSettings();
    renderSceneSettings();
    renderLightingSettings();
    renderPostProcessingSettings();
    renderColouringSettings();
    renderTransformationsSettings();
    renderFractalSettings();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::update(float deltaTime)
{
    for (auto& [name, setting] : autoChangeSettings) {
        if (setting.enabled) {
            float delta = setting.rate * deltaTime;
            if (setting.increasing) {
                setting.currentValue += delta;
                if (setting.currentValue >= setting.maxValue) {
                    setting.currentValue = setting.maxValue;
                    setting.increasing = false;
                }
            }
            else {
                setting.currentValue -= delta;
                if (setting.currentValue <= setting.minValue) {
                    setting.currentValue = setting.minValue;
                    setting.increasing = true;
                }
            }
            sceneRenderer.setUniformValue(name, setting.currentValue);
        }
    }
}

void UIManager::renderAutoChangeControls(const std::string& uniformName)
{
    auto it = autoChangeSettings.find(uniformName);
    if (it != autoChangeSettings.end()) {
        AutoChangeSetting& setting = it->second;
        ImGui::Checkbox(("Auto Change " + uniformName).c_str(), &setting.enabled);
        if (setting.enabled) {
            ImGui::SliderFloat(("Rate " + uniformName).c_str(), &setting.rate, 0.0f, 10.0f, "%.2f");
        }
    }
}

void UIManager::renderRayMarchingSettings()
{
    ImGui::SetNextWindowPos(ImVec2(152, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(190, 146), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Ray Marching Settings");
    
    float maxDist = sceneRenderer.getUniformValue("MAX_DIST");
    if (ImGui::SliderFloat("MAX_DIST", &maxDist, 0.0f, 1500.0f)) {
        sceneRenderer.setUniformValue("MAX_DIST", maxDist);
    }
    
    float maxStepsF = sceneRenderer.getUniformValue("MAX_STEPS");
    int maxSteps = static_cast<int>(maxStepsF);
    if (ImGui::SliderInt("MAX_STEPS", &maxSteps, 50, 1000)) {
        sceneRenderer.setUniformValue("MAX_STEPS", static_cast<float>(maxSteps));
    }
    
    float epsilon = sceneRenderer.getUniformValue("EPSILON");
    if (ImGui::SliderFloat("EPSILON", &epsilon, 0.00001f, 0.01f, "%.5f")) {
        sceneRenderer.setUniformValue("EPSILON", epsilon);
    }
    
    float repeatFractalF = sceneRenderer.getUniformValue("repeatFractal");
    bool repeatFractal = (repeatFractalF != 0.0f);
    if (ImGui::Checkbox("repeatFractal", &repeatFractal)) {
        sceneRenderer.setUniformValue("repeatFractal", repeatFractal ? 1.0f : 0.0f);
    }
    
    float repeatCellSize = sceneRenderer.getUniformValue("repeatCellSize");
    if (ImGui::SliderFloat("repeatCellSize", &repeatCellSize, 1.0f, 10.0f)) {
        sceneRenderer.setUniformValue("repeatCellSize", repeatCellSize);
    }

    
    ImGui::End();
}

void UIManager::renderSceneSettings()
{
    ImGui::SetNextWindowPos(ImVec2(550, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(144, 146), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Scene Settings");
    
    Eigen::Vector3f bgColorVec = sceneRenderer.getUniformVec3("backgroundColour");
    float backgroundColour[3] = { bgColorVec.x(), bgColorVec.y(), bgColorVec.z() };
    if (ImGui::ColorEdit3("backgroundColour", backgroundColour)) {
        sceneRenderer.setUniformValue("backgroundColour", backgroundColour[0], backgroundColour[1], backgroundColour[2]);
    }
    
    float useHaloF = sceneRenderer.getUniformValue("useHalo");
    bool useHalo = (useHaloF != 0.0f);
    if (ImGui::Checkbox("useHalo", &useHalo)) {
        sceneRenderer.setUniformValue("useHalo", useHalo ? 1.0f : 0.0f);
    }
    
    float useGradientF = sceneRenderer.getUniformValue("useGradient");
    bool useGradient = (useGradientF != 0.0f);
    if (ImGui::Checkbox("useGradient", &useGradient)) {
        sceneRenderer.setUniformValue("useGradient", useGradient ? 1.0f : 0.0f);
    }
    
    float haloRadius = sceneRenderer.getUniformValue("haloRadius");
    if (ImGui::SliderFloat("haloRadius", &haloRadius, 1.0f, 50.0f)) {
        sceneRenderer.setUniformValue("haloRadius", 51.0f - haloRadius);
    }
    
    Eigen::Vector3f haloColorVec = sceneRenderer.getUniformVec3("haloColour");
    float haloColour[3] = { haloColorVec.x(), haloColorVec.y(), haloColorVec.z() };
    if (ImGui::ColorEdit3("haloColour", haloColour)) {
        sceneRenderer.setUniformValue("haloColour", haloColour[0], haloColour[1], haloColour[2]);
    }
    
    ImGui::End();
}

void UIManager::renderLightingSettings()
{
    ImGui::SetNextWindowPos(ImVec2(862, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(163, 330), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Lighting Settings");
    
    Eigen::Vector3f ambientColorVec = sceneRenderer.getUniformVec3("ambientColor");
    float ambientColor[3] = { ambientColorVec.x(), ambientColorVec.y(), ambientColorVec.z() };
    if (ImGui::ColorEdit3("ambientColor", ambientColor)) {
        sceneRenderer.setUniformValue("ambientColor", ambientColor[0], ambientColor[1], ambientColor[2]);
    }
    
    Eigen::Vector3f lightSourceDirVec = sceneRenderer.getUniformVec3("lightSourceDir");
    float lightSourceDir[3] = { lightSourceDirVec.x(), lightSourceDirVec.y(), lightSourceDirVec.z() };
    if (ImGui::InputFloat3("lightSourceDir", lightSourceDir)) {
        sceneRenderer.setUniformValue("lightSourceDir", lightSourceDir[0], lightSourceDir[1], lightSourceDir[2]);
    }
    
    float specularStrength = sceneRenderer.getUniformValue("specularStrength");
    if (ImGui::SliderFloat("specularStrength", &specularStrength, 0.0f, 1.0f)) {
        sceneRenderer.setUniformValue("specularStrength", specularStrength);
    }
    
    float shininess = sceneRenderer.getUniformValue("shininess");
    if (ImGui::SliderFloat("shininess", &shininess, 1.0f, 128.0f)) {
        sceneRenderer.setUniformValue("shininess", shininess);
    }
    
    float ambientOcclusionF = sceneRenderer.getUniformValue("ambientOcclusion");
    bool ambientOcclusion = (ambientOcclusionF != 0.0f);
    if (ImGui::Checkbox("ambientOcclusion", &ambientOcclusion)) {
        sceneRenderer.setUniformValue("ambientOcclusion", ambientOcclusion ? 1.0f : 0.0f);
    }
    
    float softShadowsF = sceneRenderer.getUniformValue("softShadows");
    bool softShadows = (softShadowsF != 0.0f);
    if (ImGui::Checkbox("softShadows", &softShadows)) {
        sceneRenderer.setUniformValue("softShadows", softShadows ? 1.0f : 0.0f);
    }
    
    float shadowMaxStepsF = sceneRenderer.getUniformValue("shadowMaxSteps");
    int shadowMaxSteps = static_cast<int>(shadowMaxStepsF);
    if (ImGui::SliderInt("shadowMaxSteps", &shadowMaxSteps, 0, 20)) {
        sceneRenderer.setUniformValue("shadowMaxSteps", static_cast<float>(shadowMaxSteps));
    }

    
    float kSoftShadow = sceneRenderer.getUniformValue("kSoftShadow");
    if (ImGui::SliderFloat("kSoftShadow", &kSoftShadow, 1.0f, 20.0f)) {
        sceneRenderer.setUniformValue("kSoftShadow", kSoftShadow);
    }
    
    float lightestShadow = sceneRenderer.getUniformValue("lightestShadow");
    if (ImGui::SliderFloat("lightestShadow", &lightestShadow, 0.0f, 1.0f)) {
        sceneRenderer.setUniformValue("lightestShadow", lightestShadow);
    }
    
    float darkestShadow = sceneRenderer.getUniformValue("darkestShadow");
    if (ImGui::SliderFloat("darkestShadow", &darkestShadow, 0.0f, 1.0f)) {
        sceneRenderer.setUniformValue("darkestShadow", darkestShadow);
    }
    
    ImGui::End();
}

void UIManager::renderPostProcessingSettings()
{
    ImGui::SetNextWindowPos(ImVec2(1024, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(215, 146), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Post Processing Settings");
    
    float gammaAmount = sceneRenderer.getUniformValue("gammaAmount");
    if (ImGui::SliderFloat("gammaAmount", &gammaAmount, 1.0f, 3.0f)) {
        sceneRenderer.setUniformValue("gammaAmount", gammaAmount);
    }
    
    float contrastAmount = sceneRenderer.getUniformValue("contrastAmount");
    if (ImGui::SliderFloat("contrastAmount", &contrastAmount, 0.0f, 1.0f)) {
        sceneRenderer.setUniformValue("contrastAmount", contrastAmount);
    }
    
    float saturationAmount = sceneRenderer.getUniformValue("saturationAmount");
    if (ImGui::SliderFloat("saturationAmount", &saturationAmount, 0.0f, 2.0f)) {
        sceneRenderer.setUniformValue("saturationAmount", saturationAmount);
    }
    
    float vignetteAmount = sceneRenderer.getUniformValue("vignetteAmount");
    if (ImGui::SliderFloat("vignetteAmount", &vignetteAmount, 0.0f, 1.0f)) {
        sceneRenderer.setUniformValue("vignetteAmount", vignetteAmount);
    }
    
    Eigen::Vector3f luminanceColourVec = sceneRenderer.getUniformVec3("luminanceColour");
    float luminanceColour[3] = { luminanceColourVec.x(), luminanceColourVec.y(), luminanceColourVec.z() };
    if (ImGui::ColorEdit3("luminanceColour", luminanceColour)) {
        sceneRenderer.setUniformValue("luminanceColour", luminanceColour[0], luminanceColour[1], luminanceColour[2]);
    }
    
    ImGui::End();
}

void UIManager::renderColouringSettings()
{
    ImGui::SetNextWindowPos(ImVec2(693, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(170, 215), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Colouring Settings");
    
    float colorModeF = sceneRenderer.getUniformValue("colorMode");
    int colorMode = static_cast<int>(colorModeF);
    const char* colorModes[] = { "Fractal", "Normal", "Position", "Fractal Iterations" };
    if (ImGui::Combo("colorMode", &colorMode, colorModes, IM_ARRAYSIZE(colorModes))) {
        sceneRenderer.setUniformValue("colorMode", static_cast<float>(colorMode));
    }
    
    float positionColouringScale = sceneRenderer.getUniformValue("positionColouringScale");
    if (ImGui::SliderFloat("positionColouringScale", &positionColouringScale, 0.1f, 2.0f)) {
        sceneRenderer.setUniformValue("positionColouringScale", positionColouringScale);
    }
    
    Eigen::Vector3f positionColourOneVec = sceneRenderer.getUniformVec3("positionColourOne");
    float positionColourOne[3] = { positionColourOneVec.x(), positionColourOneVec.y(), positionColourOneVec.z() };
    if (ImGui::ColorEdit3("positionColourOne", positionColourOne)) {
        sceneRenderer.setUniformValue("positionColourOne", positionColourOne[0], positionColourOne[1], positionColourOne[2]);
    }
    
    Eigen::Vector3f positionColourTwoVec = sceneRenderer.getUniformVec3("positionColourTwo");
    float positionColourTwo[3] = { positionColourTwoVec.x(), positionColourTwoVec.y(), positionColourTwoVec.z() };
    if (ImGui::ColorEdit3("positionColourTwo", positionColourTwo)) {
        sceneRenderer.setUniformValue("positionColourTwo", positionColourTwo[0], positionColourTwo[1], positionColourTwo[2]);
    }
    
    float iterationColourVarOne = sceneRenderer.getUniformValue("iterationColourVarOne");
    if (ImGui::SliderFloat("iterationColourVarOne", &iterationColourVarOne, 0.0f, 2.0f)) {
        sceneRenderer.setUniformValue("iterationColourVarOne", iterationColourVarOne);
    }
    
    float iterationColourVarTwo = sceneRenderer.getUniformValue("iterationColourVarTwo");
    if (ImGui::SliderFloat("iterationColourVarTwo", &iterationColourVarTwo, 0.0f, 5.0f)) {
        sceneRenderer.setUniformValue("iterationColourVarTwo", iterationColourVarTwo);
    }
    
    float iterationColourVarThree = sceneRenderer.getUniformValue("iterationColourVarThree");
    if (ImGui::SliderFloat("iterationColourVarThree", &iterationColourVarThree, 0.0f, 10.0f)) {
        sceneRenderer.setUniformValue("iterationColourVarThree", iterationColourVarThree);
    }
    
    Eigen::Vector3f iterationColourVarFourVec = sceneRenderer.getUniformVec3("iterationColourVarFour");
    float iterationColourVarFour[3] = { iterationColourVarFourVec.x(), iterationColourVarFourVec.y(), iterationColourVarFourVec.z() };
    if (ImGui::ColorEdit3("iterationColourVarFour", iterationColourVarFour)) {
        sceneRenderer.setUniformValue("iterationColourVarFour", iterationColourVarFour[0], iterationColourVarFour[1], iterationColourVarFour[2]);
    }
    
    ImGui::End();
}

void UIManager::renderTransformationsSettings()
{
    ImGui::SetNextWindowPos(ImVec2(341, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(210, 215), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Transformations Settings");
    
    float useScaleF = sceneRenderer.getUniformValue("useScale");
    bool useScale = (useScaleF != 0.0f);
    if (ImGui::Checkbox("useScale", &useScale)) {
        sceneRenderer.setUniformValue("useScale", useScale ? 1.0f : 0.0f);
    }
    
    float scaleAmount = sceneRenderer.getUniformValue("scaleAmount");
    if (ImGui::SliderFloat("scaleAmount", &scaleAmount, 0.1f, 10.0f)) {
        sceneRenderer.setUniformValue("scaleAmount", scaleAmount);
    }
    
    float useTwistF = sceneRenderer.getUniformValue("useTwist");
    bool useTwist = (useTwistF != 0.0f);
    if (ImGui::Checkbox("useTwist", &useTwist)) {
        sceneRenderer.setUniformValue("useTwist", useTwist ? 1.0f : 0.0f);
    }
    
    float twistAmount = sceneRenderer.getUniformValue("twistAmount");
    if (ImGui::SliderFloat("twistAmount", &twistAmount, 0.0f, 10.0f)) {
        sceneRenderer.setUniformValue("twistAmount", twistAmount);
    }
    
    float useBendF = sceneRenderer.getUniformValue("useBend");
    bool useBend = (useBendF != 0.0f);
    if (ImGui::Checkbox("useBend", &useBend)) {
        sceneRenderer.setUniformValue("useBend", useBend ? 1.0f : 0.0f);
    }
    
    float bendAmount = sceneRenderer.getUniformValue("bendAmount");
    if (ImGui::SliderFloat("bendAmount", &bendAmount, 0.0f, 10.0f)) {
        sceneRenderer.setUniformValue("bendAmount", bendAmount);
    }
    
    float useWarpF = sceneRenderer.getUniformValue("useWarp");
    bool useWarp = (useWarpF != 0.0f);
    if (ImGui::Checkbox("useWarp", &useWarp)) {
        sceneRenderer.setUniformValue("useWarp", useWarp ? 1.0f : 0.0f);
    }
    
    float warpAmount = sceneRenderer.getUniformValue("warpAmount");
    if (ImGui::SliderFloat("warpAmount", &warpAmount, 0.0f, 0.002f, "%.5f")) {
        sceneRenderer.setUniformValue("warpAmount", warpAmount);
    }
    
    ImGui::End();
}

void UIManager::renderFractalSettings()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(154, 77), ImGuiCond_FirstUseEver); // Adjusted size for ComboBox
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);

    ImGui::Begin("Fractal Settings");
    
    Eigen::Vector3f fractalColourVec = sceneRenderer.getUniformVec3("fractalColour");
    float fractalColour[3] = { fractalColourVec.x(), fractalColourVec.y(), fractalColourVec.z() };
    if (ImGui::ColorEdit3("fractalColour", fractalColour)) {
        sceneRenderer.setUniformValue("fractalColour", fractalColour[0], fractalColour[1], fractalColour[2]);
    }
    
    static int currentFractalIndex = 0; // 0: Mandelbulb, 1: Menger Sponge
    const char* fractalTypes[] = { "Mandelbulb", "Menger Sponge" };
    static int previousFractalIndex = 0;

    if (ImGui::Combo("Fractal Type", &currentFractalIndex, fractalTypes, IM_ARRAYSIZE(fractalTypes))) {
        if (currentFractalIndex != previousFractalIndex) {
            int newFractalID = currentFractalIndex;
            
            std::string newFragmentShaderCode = glslManager.generateFragmentShader(newFractalID);
            
            if (newFragmentShaderCode.empty()) {
                std::cerr << "Failed to generate fragment shader for fractalID: " << newFractalID << std::endl;
            }
            else {
                std::string vertexShaderCode = glslManager.generateVertexShader();
                
                shaderManager.changeShader(vertexShaderCode, newFragmentShaderCode);
                
                std::unique_ptr<Fractal> newFractal;
                if (newFractalID == 0) {
                    newFractal = std::make_unique<Mandelbulb>();
                }
                else if (newFractalID == 1) {
                    newFractal = std::make_unique<MengerSponge>();
                }
                else {
                    std::cerr << "Unknown fractalID: " << newFractalID << std::endl;
                    return;
                }
                
                sceneRenderer.setFractal(std::move(newFractal));
                sceneRenderer.setFractalUniforms();
                sceneRenderer.setGlobalUniforms();
                
                initializeAutoChangeSettings();
                
                previousFractalIndex = currentFractalIndex;
            }
        }
    }
    
    //render uniform controls for the current fractal
    Fractal* fractal = sceneRenderer.getCurrentFractal();
    if (fractal) {
        const auto& fractalUniforms = fractal->getUniformNames();
        const auto& fractalAutoChange = fractal->getAutoChangeUniforms();
        for (const auto& name : fractalUniforms) {
            float value = sceneRenderer.getUniformValue(name);
            
            if (name == "Power") {
                if (ImGui::SliderFloat(name.c_str(), &value, 1.0f, 20.0f)) {
                    sceneRenderer.setUniformValue(name, value);
                }
                //auto change controls for Power if applicable
                if (fractalAutoChange.find(name) != fractalAutoChange.end()) {
                    renderAutoChangeControls(name);
                }
            }

            if (name == "mandelbulbIterations") {
                if (ImGui::SliderFloat(name.c_str(), &value, 1.001, 20.0)) {
                    sceneRenderer.setUniformValue(name, value * 1.0f);
                }
                //auto change controls for Power if applicable
                if (fractalAutoChange.find(name) != fractalAutoChange.end()) {
                    renderAutoChangeControls(name);
                }
            }
            
        }
    }
    
    ImGui::End();
}

