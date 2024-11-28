#include "camera_controller.h"

CameraController::CameraController(Camera& camera)
    : camera(camera),
      movementSpeed(1.0f),
      mouseSensitivity(0.125f),
      rotationSpeed(0.2f),
      mode(Mode::AutoRotation),
      yaw(-90.0f), //pointing towards -Z
      pitch(0.0f) {}

void CameraController::setMode(Mode newMode) {
    mode = newMode;
}

CameraController::Mode CameraController::getMode() {
    return mode;
}

void CameraController::processKeyboardInput(int key, float deltaTime, bool isShiftPressed) {
    float velocity = movementSpeed * deltaTime;
    if (mode == Mode::FreeCam) {
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
        if (key == GLFW_KEY_UP) {
            changeMovementSpeed(1);
        }
        if (key == GLFW_KEY_DOWN) {
            changeMovementSpeed(-1);
        }
        
    }
}

void CameraController::processMouseMovement(float xoffset, float yoffset) {
    if (mode == Mode::FreeCam) {
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

void CameraController::updateRotation(const Eigen::Vector3f& rotationCenter) {
    if (mode == Mode::AutoRotation) {
        float time = glfwGetTime() * rotationSpeed;
        camera.rotateAroundPoint(time, rotationCenter, 3.0f);
    }
}

void CameraController::changeRotationSpeed(int speed) {
    rotationSpeed = speed;
}

void CameraController::updateCameraVectors() {
    camera.updateCameraVectors(yaw, pitch);
}

void CameraController::changeMovementSpeed(int speed) {
    movementSpeed = speed;
}

Camera CameraController::getCamera(){
    return camera;
}