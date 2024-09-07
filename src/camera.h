#include "config.h"
#include "Eigen/Dense"

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    void setPosition(const Eigen::Vector3f& position);

    void setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

    void rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius);

    const Eigen::Matrix4f& getViewMatrix() const;

    const Eigen::Matrix4f& getProjectionMatrix() const;


private:
    Eigen::Vector3f position;
    Eigen::Matrix4f viewMatrix;
    Eigen::Matrix4f projectionMatrix;

    void updateViewMatrix(const Eigen::Vector3f& target);

};