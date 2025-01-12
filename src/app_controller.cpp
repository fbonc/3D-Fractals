#include "app_controller.h"
#include <filesystem>

AppController::AppController()
    : camera(), 
      cameraController(camera), 
      sceneRenderer(nullptr),
      uiManager(nullptr)
{
    init();
}

AppController::~AppController() {
    // GLFW cleanup
}

void AppController::init() {
    std::filesystem::current_path("C:/Users/felip/Desktop/Projects/NEA");
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;

    GLFWwindow* window = glfwManager.getWindow();
    if (!window) {
        std::cerr << "Failed to create GLFW window in AppController init." << std::endl;
        return;
    }

    glfwManager.setInputFunctions(cameraController);

    //initial shader code generation
    std::string vertexShaderCode = glslManager.generateVertexShader();
    int initialFractalID = 0; //0 = mandelbulb
    std::string fragmentShaderCode = glslManager.generateFragmentShader(initialFractalID);

    shaderManager = std::make_unique<ShaderManager>(vertexShaderCode, fragmentShaderCode);

    sceneRenderer = std::make_unique<SceneRenderer>(*shaderManager, cameraController);
    sceneRenderer->initialiseQuad();
    sceneRenderer->initialiseUniformLocations();

    sceneRenderer->setResolutionUniform((float)resolutionX, (float)resolutionY);
    
    std::unique_ptr<Fractal> initialFractal = std::make_unique<Mandelbulb>();
    sceneRenderer->setFractal(std::move(initialFractal));
    sceneRenderer->setFractalUniforms();

    uiManager = std::make_unique<UIManager>(*sceneRenderer, *shaderManager, window, glslManager);
    uiManager->init();
}


bool AppController::shouldClose() {
    GLFWwindow* window = glfwManager.getWindow();
    return (window && glfwWindowShouldClose(window));
}

void AppController::processInput() {
    glfwManager.processInput(cameraController);
}

void AppController::endFrame() {
    glfwManager.endLoop();
}

void AppController::run() {
    using clock = std::chrono::high_resolution_clock;
    auto lastTimePoint = clock::now();

    while (!shouldClose()) {
        auto currentTimePoint = clock::now();
        deltaTime = std::chrono::duration<float>(currentTimePoint - lastTimePoint).count();
        lastTimePoint = currentTimePoint;

        sceneRenderer->startLoop();

        processInput();

        cameraController.updateRotation(Eigen::Vector3f(0.0f,0.0f,0.0f));
        cameraController.updateCameraVectors();

        uiManager->update(deltaTime);
        uiManager->initRender();

        Eigen::Vector3f cameraPos = camera.getPosition();
        sceneRenderer->setCameraPosUniform(cameraPos);
        Eigen::Vector3f target = (cameraController.getMode() == CameraController::Mode::AutoRotation)
                                 ? Eigen::Vector3f(0.0f,0.0f,0.0f)
                                 : cameraPos + camera.getFront();
        sceneRenderer->setTargetUniform(target);

        sceneRenderer->setGlobalUniforms();
        sceneRenderer->setFractalUniforms();

        sceneRenderer->endLoop();
        
        uiManager->mainRender();

        endFrame();
    }

}

//test