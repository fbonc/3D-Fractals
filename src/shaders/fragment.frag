#version 330 core

out vec4 screenColor;

uniform vec3 cameraPos;
uniform mat4 view;
uniform mat4 projection;


//Cube SDF

float sdf_cube(vec3 p, vec3 size) {
    vec3 d = abs(p) - size;
    return length(max(d, 0.0)) + min(max(d.x, max(d.y, d.z)), 0.0);
}


//Ray marcher

vec3 ray_direction(float fov, vec2 fragCoord, vec2 resolution) {
    vec2 xy = fragCoord - resolution * 0.5;
    float z = resolution.y / tan(radians(fov) / 2.0);
    return normalize(vec3(xy, -z));
}


