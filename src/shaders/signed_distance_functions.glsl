#version 330 core

float pointSDF(vec3 rayPosition, vec3 pointPosition) {   

  // vector from point to ray
  vec3 pointToRay = rayPosition - pointPosition;  
  
  // Pythagorean theorem to get length of vector
  float distanceToPoint = sqrt(pointToRay.x * pointToRay.x +
                               pointToRay.y * pointToRay.y +
                               pointToRay.z * pointToRay.z);

  return distanceToPoint;
}