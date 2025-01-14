#pragma once

#include "config.h"
#include "Eigen/Dense"
#include "camera.h"


class CameraController {
public:

    CameraController(Camera& camera);

    void setMode(int newMode);
    int getMode();
    void processKeyboardInput(int key, float deltaTime, bool isShiftPressed);
    void processMouseMovement(float xoffset, float yoffset);

    void updateRotation();
    float getRotationRadius();
    void changeRotationRadius(float radius);

    float getRotationHeight();
    void changeRotationHeight(float height);

    float getMovementSpeed();
    void changeMovementSpeed(float speed);

    float getRotationSpeed();
    void changeRotationSpeed(float speed);

    void updateCameraVectors();
    Camera getCamera();

private:
    Camera& camera;  //the camera this controller is managing
    float movementSpeed;
    float mouseSensitivity;
    float rotationSpeed;
    float rotationRadius;
    float rotationHeight;

    float yaw;
    float pitch;

    int mode;

};