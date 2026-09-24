#include <fractals/shader.hpp>
#include <glad.h>
#include <iostream>

namespace {
std::string shaderInfoLog(GLuint shader) {
    GLint length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    if (length <= 1)
        return "(no info log)";
    std::string log(length, '\0');
    GLsizei written = 0;
    glGetShaderInfoLog(shader, length, &written, log.data());
    log.resize(written);
    return log;
}

std::string programInfoLog(GLuint program) {
    GLint length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    if (length <= 1)
        return "(no info log)";
    std::string log(length, '\0');
    GLsizei written = 0;
    glGetProgramInfoLog(program, length, &written, log.data());
    log.resize(written);
    return log;
}
} // namespace

std::unique_ptr<Shader> Shader::CreateFromSource(const std::string& vertexSource,
                                                 const std::string& fragmentSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    // checking for vertex shader compile errors
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "ERROR: SHADER VERTEX COMPILATION FAILED\n"
                  << shaderInfoLog(vertexShader) << std::endl;
        glDeleteShader(vertexShader);
        return nullptr;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    // checking for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cerr << "ERROR: SHADER FRAGMENT COMPILATION FAILED\n"
                  << shaderInfoLog(fragmentShader) << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return nullptr;
    }

    // link shaders into a shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::cerr << "ERROR: SHADER PROGRAM LINKING FAILED\n"
                  << programInfoLog(shaderProgram) << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        return nullptr;
    }

    // delete the shader objects now that they're linked into the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // creat eShader object
    std::unique_ptr<Shader> shader(new Shader());
    shader->shaderID = shaderProgram;

    return shader;
}

const unsigned int Shader::getShaderID() const { return shaderID; }

void Shader::deleteShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}
