#include "shader_manager.h"


unsigned int ShaderManager::make_module(const std::string& filepath, unsigned int module_type) {

	std::ifstream file;
	std::stringstream bufferedLines;
	std::string line;

	file.open(filepath);
	while (std::getline(file, line)) {
		//std::cout << line << '\n' << std::endl
		bufferedLines << line << "\n";
	}

	std::string shaderSource = bufferedLines.str();
	const char* shaderSrc = shaderSource.c_str();
	bufferedLines.str("");
	file.close();

	unsigned int shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);

	int success;
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char errorLog[1024];
		glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
		std::cout << "Shader module compilation error:\n" << errorLog << std::endl;

		// if (module_type == GL_VERTEX_SHADER) {
        //     std::cerr << "Vertex shader compilation error (" << filepath << "):\n" << errorLog << std::endl;
        // } else if (module_type == GL_FRAGMENT_SHADER) {
        //     std::cerr << "Fragment shader compilation error (" << filepath << "):\n" << errorLog << std::endl;
        // }

	}

	return shaderModule;

}


unsigned int ShaderManager::make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

	std::vector<unsigned int> modules;
	modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
	modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

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
