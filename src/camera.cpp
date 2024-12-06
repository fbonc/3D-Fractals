#include "camera.h"

Camera::Camera()
    :   front(Eigen::Vector3f(0.0f, 0.0f, -1.0f)),
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




