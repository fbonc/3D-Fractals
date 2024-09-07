#include "Camera.h"


Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane) {
    setProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);
    position = Eigen::Vector3f(0.0f, 0.0f, 3.0f);
    updateViewMatrix(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
}

void Camera::setPosition(const Eigen::Vector3f& pos) {
    position = pos;
    updateViewMatrix(Eigen::Vector3f(0.0f, 0.0f, 0.0f));
}

void Camera::setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
    projectionMatrix = Eigen::Matrix4f::Identity();
    float tanHalfFov = tan(fov / 2.0f);;

    projectionMatrix(0, 0) = 1.0f / (aspectRatio * tanHalfFov);
    projectionMatrix(1, 1) = 1.0f / tanHalfFov;
    projectionMatrix(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
    projectionMatrix(2, 3) = -1.0f;
    projectionMatrix(3, 2) = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
    projectionMatrix(3, 3) = 0.0f;

}


void Camera::rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius) {
    float camX = sin(angle) * radius;
    float camZ = cos(angle) * radius;
    position = Eigen::Vector3f(camX, 0.0f, camZ);

    updateViewMatrix(point);
}


void Camera::updateViewMatrix(const Eigen::Vector3f& target) {
    Eigen::Vector3f forward = (target - position).normalized();
    Eigen::Vector3f up = Eigen::Vector3f(0.0f, 1.0f, 0.0f);
    Eigen::Vector3f right = up.cross(forward).normalized();
    up = forward.cross(right).normalized();

    viewMatrix = Eigen::Matrix4f::Identity();
    viewMatrix.block<3, 3>(0, 0) << right, up, forward;
    viewMatrix.block<3, 1>(0, 3) = -viewMatrix.block<3, 3>(0,0) * position;

}

const Eigen::Matrix4f& Camera::getViewMatrix() const {
    return viewMatrix;
}

const Eigen::Matrix4f& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}
