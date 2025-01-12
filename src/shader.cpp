#include "shader.h"


std::unique_ptr<Shader> Shader::CreateFromSource(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    
    //checking for vertex shader compile errors
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return nullptr;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    
    //checking for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return nullptr;
    }
    
    //link shaders into a shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        return nullptr;
    }
    
    //delete the shader objects now that they're linked into the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //creat eShader object
    std::unique_ptr<Shader> shader(new Shader());
    shader->shaderID = shaderProgram;

    std::cout << "Shader: Shader program created successfully. Program ID: " << shaderProgram << std::endl;
    
    return shader;
}

const unsigned int Shader::getShaderID() const {
    return shaderID;
}



void Shader::deleteShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
}





// std::string Shader::readFile(const std::string& filepath, const unsigned int module_type) {
//     std::ifstream file(filepath);
//     if (!file.is_open()) {
//         std::cerr << "Error opening shader file: " << filepath << std::endl;
//         return "";
//     }

//     std::stringstream bufferedLines;
//     bufferedLines << file.rdbuf(); // read entire file into bufferedLines

//     return bufferedLines.str(); // return the entire file content as a string
// }


// unsigned int Shader::makeModule(const std::string& filepath, unsigned int module_type) {

//     std::string shaderSource = readFile(filepath, module_type);
//     if (shaderSource.empty()) {
//         std::cerr << "Shader source is empty for: " << filepath << std::endl;
//     }

//     const char* shaderSrc = shaderSource.c_str();
//     unsigned int shaderModule = glCreateShader(module_type);
//     glShaderSource(shaderModule, 1, &shaderSrc, NULL);
//     glCompileShader(shaderModule);

//     int success;
//     glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char errorLog[1024];
//         glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
//         std::cout << "Shader module compilation error:\n" << errorLog << std::endl;
//     }

//     return shaderModule;

// }


// unsigned int Shader::makeShader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

// 	std::vector<unsigned int> modules;
// 	modules.push_back(makeModule(vertex_filepath, GL_VERTEX_SHADER));
// 	modules.push_back(makeModule(fragment_filepath, GL_FRAGMENT_SHADER));

// 	unsigned int shader = glCreateProgram();
// 	for (unsigned int shaderModule : modules) {
// 		glAttachShader(shader, shaderModule);
// 	}

// 	glLinkProgram(shader);

// 	int success;
// 	glGetProgramiv(shader, GL_LINK_STATUS, &success);
// 	if (!success) {
// 		char errorLog[1024];
// 		glGetProgramInfoLog(shader, 1024, NULL, errorLog);
// 		std::cout << "Shader Linking error:\n" << errorLog << std::endl;
// 	}

// 	for (unsigned int shaderModule : modules) {
// 		glDeleteShader(shaderModule);
// 	}

// 	return shader;

// }
