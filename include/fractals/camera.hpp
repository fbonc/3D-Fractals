#pragma once

#include <Dense>

class Camera {
public:
    Camera();

    void setPosition(const Eigen::Vector3f& position);

    const Eigen::Vector3f& getPosition() const;

    void rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius);

    void updateCameraVectors(float yaw, float pitch);

    //getters for direction vectors
    const Eigen::Vector3f& getFront() const;
    const Eigen::Vector3f& getRight() const;
    const Eigen::Vector3f& getUp() const;
    const Eigen::Vector3f& getWorldUp() const;

private:
    Eigen::Vector3f position;
    Eigen::Vector3f front;
    Eigen::Vector3f up;
    Eigen::Vector3f right;
    Eigen::Vector3f worldUp;
};
