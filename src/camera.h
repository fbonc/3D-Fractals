#include "config.h"
#include "Eigen/Dense"

class Camera {
public:

    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    void setPosition(const Eigen::Vector3f& position);

    void rotateAroundPoint(float angle, const Eigen::Vector3f& point, float radius);

    const Eigen::Vector3f& getPosition() const;


private:

    Eigen::Vector3f position;

};