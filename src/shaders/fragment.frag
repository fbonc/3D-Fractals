#version 330 core

out vec4 screenColor;

uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;


//Cube SDF

float sdf_cube(vec3 p, vec3 size) {

    vec3 d = abs(p) - size;
    return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);

}


//Ray marcher

vec3 ray_direction(float fov, vec2 fragCoord, vec2 resolution, vec3 cameraPos, vec3 target) {

    vec2 ndc = (fragCoord / resolution) * 2.0f - 1.0f;

    ndc.y = -ndc.y;

    float aspectRatio = resolution.x / resolution.y;

    float z = 1.0/tan(radians(fov) / 2.0f);

    vec3 forward = normalize(target - cameraPos);

    vec3 right = normalize(cross(forward, vec3(0.0, 1.0, 0.0)));
    vec3 up = cross(right, forward);

    vec3 rayDir = normalize(ndc.x * right * aspectRatio + ndc.y * up + z * forward);
    return rayDir;

}



float ray_march(vec3 rayOrigin, vec3 rayDir, out vec3 hitPoint) {

    const int MAX_STEPS = 100;
    const float MAX_DIST = 100.0;
    const float SURFACE_DIST = 0.001;

    float totalDist = 0.0;
    vec3 point;

    for (int i = 0; i < MAX_STEPS; i++) {
        point = rayOrigin + rayDir * totalDist;
        float dist = sdf_cube(point, vec3(0.5)); // Cube of size 1 centered at the origin

        if (dist < SURFACE_DIST) {
            hitPoint = point;
            return totalDist;
        }
        
        totalDist += dist;

        if (totalDist > MAX_DIST)
            break;
    }

    return -1.0; // No hit

}



void main() {

    vec2 fragCoord = gl_FragCoord.xy;
    vec2 resolution = vec2(resolution.x, resolution.y);
    
    //Get ray direction
    vec3 rayDir = ray_direction(45.0f, fragCoord, resolution, cameraPos, target);
    vec3 rayOrigin = cameraPos;

    vec3 hitPoint;
    float distance = ray_march(rayOrigin, rayDir, hitPoint);

    if (distance > 0.0) {
        //Color the cube based on its normal
        vec3 normal = normalize(hitPoint);  //Simple approximation
        screenColor = vec4(normal * 0.5 + 0.5, 1.0); //Basic shading
    } else {
        // Background color
        screenColor = vec4(0.0, 0.0, 0.0, 1.0); //Black background
    }

}
