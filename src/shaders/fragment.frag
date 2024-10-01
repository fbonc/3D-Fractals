#version 330 core


out vec4 screenColor;

uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;
uniform bool isRepeating;
uniform float Power;

#define MAX_DIST 200.0
#define MAX_STEPS 200
#define EPSILON 0.0001



float cubeSDF(vec3 rayPos, float width) {
  //half initial scale of square (arbitrary)
    float halfWidth = width / 2.0;
    vec3 corner = vec3(halfWidth, halfWidth, halfWidth);

    //fold ray into positive octant
    vec3 foldedPos = abs(rayPos);
    //corner to ray
    vec3 ctr = foldedPos - corner;

    //ignore negative components for outside points
    vec3 closestToOutsideRay = max(ctr, 0.0);

    float cornerToRayMaxComponent = max(max(ctr.x, ctr.y), ctr.z);
    float distToInsideRay = min(cornerToRayMaxComponent, 0.0);

    // return either the distance to outside OR distance to inside
    return length(closestToOutsideRay) + distToInsideRay;
} 



float sdCross(vec3 rayPos, float width) {
    float halfWidth = width / 2.0;
    vec3 corner = vec3(halfWidth, halfWidth, halfWidth);
    vec3 foldedPos = abs(rayPos);

    //corner to ray
    vec3 ctr = foldedPos - corner;

    float minComp = min(min(ctr.x, ctr.y), ctr.z);
    float maxComp = max(max(ctr.x, ctr.y), ctr.z);

    //acquire middle component
    float midComp = ctr.x + ctr.y + ctr.z - minComp - maxComp;

    vec2 closestOutsidePoint = max(vec2(minComp, midComp), 0.0);
    vec2 closestInsidePoint = min(vec2(midComp, maxComp), 0.0);

    // return either the distance to inside OR outside
    return length(closestOutsidePoint) + -length(closestInsidePoint);
}



float mengerSpongeSDF(vec3 rayPos, int numIterations, float cubeWidth) {
  const float oneThird = 1.0 / 3.0;
  float spongeCube = cubeSDF(rayPos, cubeWidth);
  float mengerSpongeDist = spongeCube;
  
  float scale = 1.0;
  for(int i = 0; i < numIterations; ++i) {
    //determine repeated box width
    float boxedWidth = cubeWidth / scale;
    
    float translation = -boxedWidth / 2.0;
    vec3 ray = rayPos - translation;
    vec3 repeatedPos = mod(ray, boxedWidth);
    repeatedPos += translation;
    
    //scale coordinate systems from 
    //[-1/scale, 1/scale) -> to [-1.0, 1.0)
    repeatedPos *= scale;
    
    float crossesDist = sdCross(repeatedPos / oneThird, cubeWidth) * oneThird;
    
    //acquire actual distance by un-stretching
    crossesDist /= scale;
    
    mengerSpongeDist = max(mengerSpongeDist, -crossesDist);
    
    scale *= 3.0;
  }
  return mengerSpongeDist;
}

float mandelbulbSDF(vec3 rayPos) {

    vec3 currentPoint = rayPos;
    float radius = 0.0;  //distance from the origin
    float derivative = 1.0;  //derivative used for distance estimation
    // float Power = 8.0;

    for (int i = 0; i < 40; i++) {

        radius = length(currentPoint);
        if (radius > 4.0) break;  //early exit if outside the bounding radius

        //convert current point to polar coordinates
        float polarAngle = acos(currentPoint.z / radius);
        float azimuthalAngle = atan(currentPoint.y, currentPoint.x);
        
        //update derivative
        derivative = pow(radius, Power - 1.0) * Power * derivative + 1.0;

        //scale and rotate the point based on the current radius and angles
        float scaledRadius = pow(radius, Power);
        polarAngle *= Power;
        azimuthalAngle *= Power;

        //convert back to cartesian coordinates
        currentPoint = scaledRadius * vec3(
            sin(polarAngle) * cos(azimuthalAngle),
            sin(azimuthalAngle) * sin(polarAngle),
            cos(polarAngle)
        );
        currentPoint += rayPos;

    }

    return 0.5 * log(radius) * radius / derivative;  //final distance estimation

}

//signed distance function for a sphere
float sphereSDF(vec3 rayPos, vec3 center, float radius) {

    return length(rayPos - center) - radius;

}



vec3 repeat(vec3 rayPos, vec3 cell_width) {

    return mod(rayPos + 0.5 * cell_width, cell_width) - 0.5 * cell_width; //repeat space in all directions

}




//Ray marcher

vec3 ray_direction(float fov, vec2 fragCoord, vec2 resolution, vec3 cameraPos, vec3 target) {
    vec2 ndc = (fragCoord / resolution) * 2.0f - 1.0f;  //normalize device coordinates
    ndc.x *= resolution.x / resolution.y;  //aspect ratio correction

    vec3 forward = normalize(target - cameraPos);
    vec3 right = normalize(cross(forward, vec3(0.0, 1.0, 0.0)));
    vec3 up = cross(right, forward);

    vec3 rayDir = normalize(ndc.x * right + ndc.y * up + forward);
    rayDir = normalize(rayDir);

    if (dot(rayDir, forward) < 0.0) {
        rayDir = -rayDir;
    }

    return rayDir;
}



float ray_march(vec3 rayOrigin, vec3 rayDir, out int steps, out vec3 hitPoint) {

    float totalDist = 0.0;

    steps = 0;

    for (int i = 0; i < MAX_STEPS; i++) {

        steps += 1;
        vec3 point = rayOrigin + rayDir * totalDist;

        //vec3 repeatedPoint = repeat(point, vec3(6.7)); //repeat object infinitely in all directions
        float dist = mandelbulbSDF(point);
        // float dist = mengerSpongeSDF(point, 7, 10);


        if (abs(dist) < EPSILON) {
            hitPoint = point;
            return totalDist;
        }
        
        totalDist += dist;

        if (abs(totalDist) > MAX_DIST) break;
        
    }

    return totalDist; //no hit

}



void main() {

    vec2 fragCoord = gl_FragCoord.xy;
    vec2 resolution = vec2(resolution.x, resolution.y);
    
    vec3 rayDir = ray_direction(35.0f, fragCoord, resolution, cameraPos, target);
    vec3 rayOrigin = cameraPos;

    vec3 hitPoint;
    int steps;
    float distance = ray_march(rayOrigin, rayDir, steps, hitPoint);

    if (distance < MAX_DIST) {

        vec3 color = vec3(0.6 - (float(steps) / float(MAX_STEPS))); //white objects
        screenColor = vec4(color, 1.0);

    } else {

        screenColor = vec4(0.2, 0.2, 0.2, 1.0); //black background
    }

}
