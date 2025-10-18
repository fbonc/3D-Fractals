#pragma once

#include "config.h"
#include "internal/shader.hpp"
#include <memory>

class ShaderManager {
    public:
        ShaderManager(const std::string& vertexSource, const std::string& fragmentSource);
        void deleteShader();
        void changeShader(const std::string& vertexSource, const std::string& fragmentSource);
        const std::unique_ptr<Shader>& getShaderProgram() const;

    private:
        std::unique_ptr<Shader> shaderProgram;
    
};