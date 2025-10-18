#include <fractals/camera_controller.hpp>

#include <Eigen/Dense>
#include <GLFW/glfw3.h>

CameraController::CameraController(Camera& camera)
    : camera(camera),
      movementSpeed(1.0f),
      mouseSensitivity(0.125f),
      rotationSpeed(0.2f),
      mode(0),
      yaw(-90.0f), //pointing towards -Z
      rotationRadius(3.0f),
      rotationHeight(0.0f),
      pitch(0.0f) {}

void CameraController::setMode(int newMode) {
    mode = newMode;
}

int CameraController::getMode() {
    return mode;
}

void CameraController::processKeyboardInput(int key, float deltaTime, bool isShiftPressed) {
    float velocity = movementSpeed * deltaTime;
    if (mode == 1) {
        if (isShiftPressed) {
            velocity *= 6.0f;
        }
        if (key == GLFW_KEY_W) {
            camera.setPosition(camera.getPosition() + camera.getFront() * velocity);
        }
        if (key == GLFW_KEY_S) {
            camera.setPosition(camera.getPosition() - camera.getFront() * velocity);
        }
        if (key == GLFW_KEY_A) {
            camera.setPosition(camera.getPosition() - camera.getRight() * velocity);
        }
        if (key == GLFW_KEY_D) {
            camera.setPosition(camera.getPosition() + camera.getRight() * velocity);
        }
        if (key == GLFW_KEY_SPACE) {
            camera.setPosition(camera.getPosition() + camera.getWorldUp() * velocity);
            std::cout << "space" << std::endl;
        }
        if (key == GLFW_KEY_LEFT_CONTROL) {
            camera.setPosition(camera.getPosition() - camera.getWorldUp() * velocity);
            std::cout << "ctrl" << std::endl;
        }
        
    }
}

void CameraController::processMouseMovement(float xoffset, float yoffset) {
    if (mode == 1) {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        updateCameraVectors();
    }
}

void CameraController::updateRotation() {
    if (mode == 0) {
        float time = glfwGetTime() * rotationSpeed;
        camera.rotateAroundPoint(time, Eigen::Vector3f(0.0f,rotationHeight,0.0f), rotationRadius);
    }
}

float CameraController::getRotationHeight() {
    return rotationHeight;
}

void CameraController::changeRotationHeight(float height) {
    rotationHeight = height;
}



float CameraController::getRotationRadius() {
    return rotationRadius;
}

void CameraController::changeRotationRadius(float radius) {
    rotationRadius = radius;
}


float CameraController::getRotationSpeed() {
    return rotationSpeed;
}

void CameraController::changeRotationSpeed(float speed) {
    rotationSpeed = speed;
}


float CameraController::getMovementSpeed() {
    return movementSpeed;
}

void CameraController::changeMovementSpeed(float speed) {
    movementSpeed = speed;
}


void CameraController::updateCameraVectors() {
    camera.updateCameraVectors(yaw, pitch);
}

Camera CameraController::getCamera(){
    return camera;
}