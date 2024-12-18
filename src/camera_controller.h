#pragma once

#include "config.h"
#include "Eigen/Dense"
#include "camera.h"


class CameraController {
public:
    enum class Mode { FreeCam, AutoRotation };

    CameraController(Camera& camera);

    void setMode(Mode newMode);
    CameraController::Mode getMode();
    void processKeyboardInput(int key, float deltaTime, bool isShiftPressed);
    void processMouseMovement(float xoffset, float yoffset);

    void updateRotation(const Eigen::Vector3f& rotationCenter);
    void updateCameraVectors();
    void changeMovementSpeed(int speed);
    void changeRotationSpeed(int speed);
    Camera getCamera();

private:
    Camera& camera;  //the camera this controller is managing
    float movementSpeed;
    float mouseSensitivity;
    float rotationSpeed;

    float yaw;
    float pitch;

    Mode mode;

    //update camera orientation based on yaw and pitch

};