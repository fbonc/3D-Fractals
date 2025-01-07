vec3 repeat(vec3 rayPos, vec3 cell_width) {

    return mod(rayPos + 0.5 * cell_width, cell_width) - 0.5 * cell_width; //repeat space in all directions

}


vec3 ray_direction(vec2 fragCoord, vec2 resolution, vec3 cameraPos, vec3 target) {
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



float ray_march(vec3 rayOrigin, vec3 rayDir, out int steps, out vec3 hitPoint, out float colorFactor) {

    float totalDist = 0.0;

    steps = 0;

    for (int i = 0; i < MAX_STEPS; i++) {

        steps += 1;
        vec3 point = rayOrigin + rayDir * abs(totalDist);


        if (repeatFractal) {
            point = repeat(point, vec3(repeatCellSize)); //repeat object infinitely in all directions
        }

        point = applyTransformations(point);

        vec2 distAndColor = SDF(point);

        float dist = distAndColor.x;


        if (abs(dist) < EPSILON) {
            hitPoint = point;
            colorFactor = distAndColor.y;
            return totalDist;
        }
        
        totalDist += dist;

        if (totalDist > MAX_DIST) break;
        
    }

    return totalDist; //no hit

}