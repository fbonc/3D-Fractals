#include "Camera.h"


Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane) {

    position = Eigen::Vector3f(0.0f, 0.0f, 3.0f);

}

void Camera::setPosition(const Eigen::Vector3f& pos) {

    position = pos;

}


void Camera::rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius) {

    float camX = sin(angle) * radius;
    float camZ = cos(angle) * radius;

    position = Eigen::Vector3f(camX, 0.0f, camZ);

}

const Eigen::Vector3f& Camera::getPosition() const {
    return position;
}


