#version 330 core


out vec4 screenColor;

uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;
uniform vec3 lightPos;


//Cube SDF

float cubeSDF(vec3 p, vec3 size) {

    vec3 d = abs(p) - size;
    return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);

}


float cubeSDF(vec3 rayPos) {
  //half initial scale of square (arbitrary)
  const float halfWidth = 1.0;
  const vec3 corner = vec3(halfWidth, halfWidth, halfWidth);

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


float sphereSDF(vec3 p, float size) {

    return length(p) - size;

}


vec3 repeat(vec3 p, vec3 c) {

    return mod(p + 0.5 * c, c) - 0.5 * c; //repeat space in all directions with cell size c

}




//Ray marcher

vec3 ray_direction(float fov, vec2 fragCoord, vec2 resolution, vec3 cameraPos, vec3 target) {

    vec2 ndc = (fragCoord / resolution) * 2.0f - 1.0f;
    //ndc.y = -ndc.y;

    float aspectRatio = resolution.x / resolution.y;
    float z = 1.0/tan(radians(fov) / 2.0f);

    vec3 forward = normalize(target - cameraPos);
    vec3 right = normalize(cross(forward, vec3(0.0, 1.0, 0.0)));
    vec3 up = cross(right, forward);

    vec3 rayDir = normalize(ndc.x * right * aspectRatio + ndc.y * up + z * forward);
    return rayDir;

}



float ray_march(vec3 rayOrigin, vec3 rayDir, out vec3 hitPoint, out int iterations, out int max_steps) {

    const int MAX_STEPS = 100;
    const float MAX_DIST = 100.0;
    const float SURFACE_DIST = 0.01;

    float totalDist = 0.0;

    vec3 point;
    int iteration_num;

    for (int i = 0; i < MAX_STEPS; i++) {
        iteration_num += 1;

        point = rayOrigin + rayDir * totalDist;


        //repeat object infinitely in all directions
        vec3 repeatedPoint = repeat(point, vec3(2.0));
        float dist = sphereSDF(repeatedPoint, 0.4);


        //float dist = sphereSDF(point, 1);

        if (dist < SURFACE_DIST) {
            hitPoint = point;
            iterations = iteration_num;
            max_steps = MAX_STEPS;

            return totalDist;
        }
        
        totalDist += dist;

        if (totalDist > MAX_DIST)
            break;
    }

    return -1.0; // no hit

}



void main() {

    vec2 fragCoord = gl_FragCoord.xy;
    vec2 resolution = vec2(resolution.x, resolution.y);
    
    vec3 rayDir = ray_direction(45.0f, fragCoord, resolution, cameraPos, target);
    vec3 rayOrigin = cameraPos;

    vec3 hitPoint;
    int iterations;
    int max_steps;
    float distance = ray_march(rayOrigin, rayDir, hitPoint, iterations, max_steps);

    if (distance > 0.0) {

        screenColor = vec4(1.0 - (float(iterations) / float(max_steps)));
        //screenColor = vec4(1.0, 1.0, 1.0, 1.0);

    } else {

        screenColor = vec4(0.2, 0.2, 0.2, 1.0); //black background
    }

}
