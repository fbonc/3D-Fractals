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

    void rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius);
    void updateRotation(float deltaTime, const Eigen::Vector3f& rotationCenter);
    void updateCameraVectors();
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