#include <filesystem>
#include <fractals/glsl_manager.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <array>
#include <unistd.h>
#endif

namespace {
std::filesystem::path executableDirectory() {
#if defined(_WIN32)
    std::wstring path(32768, L'\0');
    DWORD length = GetModuleFileNameW(nullptr, path.data(), static_cast<DWORD>(path.size()));
    if (length > 0 && length < path.size()) {
        path.resize(length);
        return std::filesystem::path(path).parent_path();
    }
#elif defined(__APPLE__)
    uint32_t length = 0;
    _NSGetExecutablePath(nullptr, &length);
    std::string path(length, '\0');
    if (_NSGetExecutablePath(path.data(), &length) == 0) {
        return std::filesystem::canonical(path.c_str()).parent_path();
    }
#elif defined(__linux__)
    std::array<char, 4096> path;
    ssize_t length = readlink("/proc/self/exe", path.data(), path.size());
    if (length > 0 && static_cast<size_t>(length) < path.size()) {
        return std::filesystem::path(std::string(path.data(), length)).parent_path();
    }
#endif
    return std::filesystem::path(FRACTALS_ASSET_DIR).parent_path();
}
} // namespace

std::string GLSLManager::generateVertexShader() {
    std::string vertexShaderCode = readShaderFile("assets/shaders/util/vertex.vert");
    return vertexShaderCode;
}

std::string GLSLManager::generateFragmentShader(const int& fractalID) {
    std::string uniformsCode = readShaderFile(universalUniformsPath);
    std::string perlinNoiseCode = readShaderFile(perlinNoisePath);
    std::string transformationsCode = readShaderFile(transformationsPath);
    std::string colouringCode = readShaderFile(colouringPath);
    std::string lightingCode = readShaderFile(lightingPath);
    std::string backgroundCode = readShaderFile(backgroundPath);
    std::string postProcessingCode = readShaderFile(postProcessingPath);
    std::string rayMarchingCode = readShaderFile(rayMarchingPath);
    std::string mainCode = readShaderFile(mainPath);

    // fractal specific code based on fractalID
    std::string fractalCode = getFractalCode(fractalID);

    // full fragment shader code
    std::ostringstream fragmentShaderStream;
    fragmentShaderStream << "#version 330 core\n\n";
    fragmentShaderStream << "out vec4 screenColor;\n\n";

    fragmentShaderStream << uniformsCode << "\n";
    fragmentShaderStream << fractalCode << "\n";
    fragmentShaderStream << perlinNoiseCode << "\n";
    fragmentShaderStream << transformationsCode << "\n";
    fragmentShaderStream << colouringCode << "\n";
    fragmentShaderStream << lightingCode << "\n";
    fragmentShaderStream << backgroundCode << "\n";
    fragmentShaderStream << postProcessingCode << "\n";
    fragmentShaderStream << rayMarchingCode << "\n";
    fragmentShaderStream << mainCode << "\n";

    return fragmentShaderStream.str();
}

std::string GLSLManager::readShaderFile(const std::string& filepath) const {
    const auto relativePath = std::filesystem::path(filepath).lexically_relative("assets");
    const auto packagedPath = executableDirectory() / "assets" / relativePath;
    const auto sourcePath = std::filesystem::path(FRACTALS_ASSET_DIR) / relativePath;
    const auto fullPath = std::filesystem::exists(packagedPath) ? packagedPath : sourcePath;
    std::ifstream fileStream(fullPath);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open shader file: " + fullPath.string());
    }

    std::ostringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}

std::string GLSLManager::getFractalCode(const int& fractalID) const {

    switch (fractalID) {
    case 0:
        return readShaderFile(mandelbulbPath);
    case 1:
        return readShaderFile(mengerSpongePath);
    case 2:
        return readShaderFile(juliaPath);
    case 3:
        return readShaderFile(kleinianPath);
    case 4:
        return readShaderFile(mandelboxPath);
    default:
        std::cerr << "Error: Unknown fractalID " << fractalID << std::endl;
        return "";
    }
}
