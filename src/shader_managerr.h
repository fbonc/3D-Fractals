#pragma once

#include "config.h"
#include "shader.h"
#include <memory>

class ShaderManager {
    public:
        ShaderManager(const std::string& vertex_filepath, const std::string& fragment_filepath);
        void deleteShader();
        void changeShader(const std::string& vertex_filepath, const std::string& fragment_filepath);
        const std::unique_ptr<Shader>& getShaderProgram() const;

    private:
        std::unique_ptr<Shader> createShader(const std::string& vertex_filepath, const std::string& fragment_filepath);
        std::unique_ptr<Shader> shaderProgram;
    
};