#include "shader_managerr.h"
#include "camera_controller.h"
#include "glfw_manager.h"
#include "config.h"
#include "unordered_map"


class SceneRenderer
{
private:
    std::unordered_map<std::string, int> uniformLocations;
    const ShaderManager& shaderManager;

    template<typename T>
    void setUniformByType(int location, T value);
    void mainRenderLoop();

public:
    SceneRenderer(const ShaderManager& shaderManager, const Camera& cameraInput);
    ~SceneRenderer();

    void setUniformLocations(const std::vector<std::string>& uniformNames);
    int getUniformLocation(const std::string& uniformName);

    template<typename T>
    void setUniform(const std::string& uniformName, T value);
    
    Camera camera;
    CameraController cameraController;
};

