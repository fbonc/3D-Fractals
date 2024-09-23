#include "camera.h"

Camera::Camera()
    : front(Eigen::Vector3f(0.0f, 0.0f, -1.0f)),
      worldUp(Eigen::Vector3f(0.0f, 1.0f, 0.0f)) {
    position = Eigen::Vector3f(0.0f, 0.0f, 3.0f);
}

void Camera::setPosition(const Eigen::Vector3f& pos) {
    position = pos;
}

const Eigen::Vector3f& Camera::getPosition() const {
    return position;
}

void Camera::rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius) {
    float camX = sin(angle) * radius;
    float camZ = cos(angle) * radius;
    position = Eigen::Vector3f(point[0] + camX, point[1] + 0.0f, point[2] + camZ);
}

void Camera::updateCameraVectors(float yaw, float pitch) {
    Eigen::Vector3f frontVector;
    frontVector.x() = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    frontVector.y() = sin(pitch * M_PI / 180.0f);
    frontVector.z() = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
    front = frontVector.normalized();

    right = front.cross(worldUp).normalized();
    up = right.cross(front).normalized();
}

const Eigen::Vector3f& Camera::getFront() const {
    return front;
}

const Eigen::Vector3f& Camera::getRight() const {
    return right;
}

const Eigen::Vector3f& Camera::getUp() const {
    return up;
}

const Eigen::Vector3f& Camera::getWorldUp() const {
    return worldUp;
}




// #include "Camera.h"


// Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
//     : front(Eigen::Vector3f(0.0f, 0.0f, -1.0f)),
//     worldUp(Eigen::Vector3f(0.0f, 1.0f, 0.0f)),
//     yaw(-90.0f), //pointing towards -z
//     pitch(0.0f),
//     movementSpeed(2.5f),
//     mouseSensitivity(0.1f),
//     rotationSpeed(0.2f),
//     mode(Mode::AutoRotation) {

//     position = Eigen::Vector3f(0.0f, 0.0f, 3.0f);
//     updateCameraVectors();

// }

// void Camera::setPosition(const Eigen::Vector3f& pos) {

//     position = pos;

// }


// const Eigen::Vector3f& Camera::getPosition() const {

//     return position;

// }



// void Camera::updateCameraVectors() {

//     Eigen::Vector3f frontVector;
//     frontVector.x() = cos(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
//     frontVector.y() = sin(pitch * M_PI / 180.0f);
//     frontVector.z() = sin(yaw * M_PI / 180.0f) * cos(pitch * M_PI / 180.0f);
//     front = frontVector.normalized();

//     right = front.cross(worldUp).normalized();
//     up = right.cross(front).normalized();
    
// }

// void Camera::processKeyboardInput(int key, float deltaTime) {
//     float velocity = movementSpeed * deltaTime;
//     if (mode == Mode::FreeCam) {
//         if (key == GLFW_KEY_W)
//             position += front * velocity;
//         if (key == GLFW_KEY_S)
//             position -= front * velocity;
//         if (key == GLFW_KEY_A)
//             position -= right * velocity;
//         if (key == GLFW_KEY_D)
//             position += right * velocity;
//     }
// }


// void Camera::processMouseMovement(float xoffset, float yoffset) {
//     if (mode == Mode::FreeCam) {
//         xoffset *= mouseSensitivity;
//         yoffset *= mouseSensitivity;

//         yaw += xoffset;
//         pitch += yoffset;

//         if (pitch > 89.0f)
//             pitch = 89.0f;
//         if (pitch < -89.0f)
//             pitch = -89.0f;

//         updateCameraVectors();
//     }
// }

// void Camera::update(float deltaTime, const Eigen::Vector3f& rotationCenter) {
//     if (mode == Mode::AutoRotation) {
//         float time = glfwGetTime() * rotationSpeed;
//         rotateAroundPoint(time, rotationCenter, 1.0f);
//     }
// }

// void Camera::rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius) {

//     float camX = sin(angle) * radius;
//     float camZ = cos(angle) * radius;

//     position = Eigen::Vector3f(point[0] + camX, point[1] + 0.0f, point[2] + camZ);

// }

// void Camera::setMode(Mode newMode) {
//     mode = newMode;
// }

// Camera::Mode Camera::getMode() const {
//     return mode;
// }




