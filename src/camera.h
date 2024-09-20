#include "config.h"
#include "Eigen/Dense"

class Camera {
public:
    enum class Mode { FreeCam, AutoRotation };

    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    void setPosition(const Eigen::Vector3f& position);

    void rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius);

    const Eigen::Vector3f& getPosition() const;

    //update camera based on current mode
    void update(float deltaTime, const Eigen::Vector3f& rotationCenter);

    //free cam controls
    void processKeyboardInput(int key, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);

    void setMode(Mode newMode);
    Mode getMode() const;

private:

    Eigen::Vector3f position;
    Eigen::Vector3f front;
    Eigen::Vector3f up;
    Eigen::Vector3f right;
    Eigen::Vector3f worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float rotationSpeed;

    Mode mode;

    //update camera orientation vectors based on yaw and pitch
    void updateCameraVectors();
};