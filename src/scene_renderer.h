#include "shader_managerr.h"
#include "config.h"
#include "unordered_map"


class SceneRenderer
{
private:
    std::unordered_map<std::string, int> uniformLocations;
    const ShaderManager& shaderManager;

    template<typename T>
    void setUniformByType(int location, T value);
public:
    SceneRenderer(const ShaderManager& shaderManager);
    ~SceneRenderer();

    void setUniformLocations(const std::vector<std::string>& uniformNames);
    int getUniformLocation(const std::string& uniformName);

    template<typename T>
    void setUniform(const std::string& uniformName, T value);
};

