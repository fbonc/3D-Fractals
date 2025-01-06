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
    std::filesystem::current_path(R"(C:\Users\felip\Desktop\dev\NEA)");
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;

    GLFWwindow* window = glfwManager.getWindow();
    if (!window) {
        std::cerr << "Failed to create GLFW window in AppController init." << std::endl;
        return;
    }

    glfwManager.setInputFunctions(cameraController);

    createShader();

    sceneRenderer = std::make_unique<SceneRenderer>(*shaderManager, cameraController);
    sceneRenderer->initialiseQuad();
    sceneRenderer->initialiseUniformLocations();

    sceneRenderer->setResolutionUniform((float)resolutionX, (float)resolutionY);
    
    std::unique_ptr<Fractal> initialFractal = std::make_unique<Mandelbulb>();
    sceneRenderer->setFractal(std::move(initialFractal));

    uiManager = std::make_unique<UIManager>(*sceneRenderer, *shaderManager, window);
    uiManager->init();
}

void AppController::createShader() {
    // using existing vertex and fragment shader files
    //integrate GLSLManager later to generate them dynamically
    std::string vertexFile = "shaders/vertex.vert";
    std::string fragmentFile = "shaders/fragment2.frag";

    shaderManager = std::make_unique<ShaderManager>(vertexFile, fragmentFile);
    glUseProgram(shaderManager->getShaderProgram()->getShaderID());
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
        uiManager->render();

        Eigen::Vector3f cameraPos = camera.getPosition();
        sceneRenderer->setCameraPosUniform(cameraPos);
        Eigen::Vector3f target = (cameraController.getMode() == CameraController::Mode::AutoRotation)
                                 ? Eigen::Vector3f(0.0f,0.0f,0.0f)
                                 : cameraPos + camera.getFront();
        sceneRenderer->setTargetUniform(target);

        sceneRenderer->setGlobalUniforms();
        sceneRenderer->setFractalUniforms();

        sceneRenderer->endLoop();

        endFrame();
    }

}
