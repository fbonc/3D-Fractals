#include "config.h"

class Shader {
    public:
        Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
        
        unsigned int makeModule(const std::string& filepath, unsigned int module_type);
        unsigned int makeShader(const std::string& vertex_filepath, const std::string& fragment_filepath);
        const char* readFile(const std::string& filepath) const;

        void deleteShader();

        const unsigned int getShaderID() const;

    private:
        unsigned int shaderID;

};