#include "shader.h"

Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {
    shaderID = makeShader(vertex_filepath, fragment_filepath);
}

const unsigned int Shader::getShaderID() const {
    return shaderID;
}


std::string Shader::readFile(const std::string& filepath, const unsigned int module_type) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening shader file: " << filepath << std::endl;
        return "";
    }

    std::stringstream bufferedLines;
    bufferedLines << file.rdbuf(); // read entire file into bufferedLines

    return bufferedLines.str(); // return the entire file content as a string
}


unsigned int Shader::makeModule(const std::string& filepath, unsigned int module_type) {

    std::string shaderSource = readFile(filepath, module_type);
    if (shaderSource.empty()) {
        std::cerr << "Shader source is empty for: " << filepath << std::endl;
    }

    const char* shaderSrc = shaderSource.c_str();
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader module compilation error:\n" << errorLog << std::endl;
    }

    return shaderModule;

}


unsigned int Shader::makeShader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

	std::vector<unsigned int> modules;
	modules.push_back(makeModule(vertex_filepath, GL_VERTEX_SHADER));
	modules.push_back(makeModule(fragment_filepath, GL_FRAGMENT_SHADER));

	unsigned int shader = glCreateProgram();
	for (unsigned int shaderModule : modules) {
		glAttachShader(shader, shaderModule);
	}

	glLinkProgram(shader);

	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
		std::cout << "Shader Linking error:\n" << errorLog << std::endl;
	}

	for (unsigned int shaderModule : modules) {
		glDeleteShader(shaderModule);
	}

	return shader;

}

void Shader::deleteShader() {
	glDeleteProgram(shaderID);
}