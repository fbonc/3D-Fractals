#pragma once

#include <string>
#include <memory>


class Shader {
public:
    static std::unique_ptr<Shader> CreateFromSource(const std::string& vertexSource, const std::string& fragmentSource);
    void deleteShader();
    const unsigned int getShaderID() const;

private:
    Shader() : shaderID(0) {} //private constructor to enforce creation using factory method

    unsigned int shaderID;
};