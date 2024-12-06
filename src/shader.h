#pragma once

#include "config.h"

class Shader {
    public:
        Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
        void deleteShader();
        const unsigned int getShaderID() const;
        const std::string& getShaderName() const;




    private:
        unsigned int makeModule(const std::string& filepath, unsigned int module_type);
        unsigned int makeShader(const std::string& vertex_filepath, const std::string& fragment_filepath);

        const char* readFile(const std::string& filepath, const unsigned int module_type);
        unsigned int shaderID;
        std::string shaderName;
};