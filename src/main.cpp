#include <exception>
#include <fractals/app_controller.hpp>
#include <iostream>

int main() {
    try {
        AppController app;
        app.run();
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}
