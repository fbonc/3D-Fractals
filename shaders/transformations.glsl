vec3 scale(vec3 p, float k) {
    return p / k;
}

vec3 twist(vec3 p, float k) {
    float c = cos(k * p.y);
    float s = sin(k * p.y);
    mat2 m = mat2(c, -s, s, c);
    return vec3(m * p.xz, p.y);
}


vec3 bend(vec3 p, float k) {
    float c = cos(k * p.x);
    float s = sin(k * p.x);
    mat2 m = mat2(c, -s, s, c);
    return vec3(p.x, m * p.yz);
}

vec3 warp(vec3 p, float k) {
    p += k * vec3(
        noise(p + vec3(0.0)),
        noise(p + vec3(100.0)),
        noise(p + vec3(200.0))
    );
    return p;
}


vec3 applyTransformations(vec3 rayOrigin) {

    if (useScale) {
        rayOrigin = scale(rayOrigin, scaleAmount);
    }
    if (useTwist) {
        rayOrigin = twist(rayOrigin, twistAmount);
    }
    if (useBend) {
        rayOrigin = bend(rayOrigin, bendAmount);
    }
    if (useWarp) {
        rayOrigin = warp(rayOrigin, warpAmount);
    }

    return rayOrigin;
}
