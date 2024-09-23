#include "camera_controller.h"

CameraController::CameraController(Camera& camera)
    : camera(camera),
      movementSpeed(2.5f),
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
            velocity *= 2.0f;
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

void CameraController::rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius) {
    if (mode == Mode::AutoRotation) {
        camera.rotateAroundPoint(angle, point, radius);
    }
}

void CameraController::updateRotation(float deltaTime, const Eigen::Vector3f& rotationCenter) {
    if (mode == Mode::AutoRotation) {
        float time = glfwGetTime() * rotationSpeed;
        rotateAroundPoint(time, rotationCenter, 1.0f);
    }
}

void CameraController::updateCameraVectors() {
    camera.updateCameraVectors(yaw, pitch);
}