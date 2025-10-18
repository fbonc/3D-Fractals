void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 q = fragCoord.xy / resolution.xy;
    vec2 res = vec2(resolution.x, resolution.y);

    vec3 rayDir = ray_direction(fragCoord, res, cameraPos, target);
    vec3 rayOrigin = cameraPos;

    vec3 hitPoint;
    int steps;
    float colorFactor;

    float distance = ray_march(rayOrigin, rayDir, steps, hitPoint, colorFactor);

    vec3 lightDir = normalize(lightSourceDir);

    vec3 finalColor;

    if (distance < MAX_DIST) {
        vec3 normal = estimateNormal(hitPoint);

        vec3 viewDir = normalize(cameraPos - hitPoint);

        vec3 lightDirection = normalize(lightDir);

        vec3 objectColor = getColor(steps, normal, hitPoint, distance, colorFactor);

        finalColor = calculateLighting(hitPoint, normal, viewDir, lightDirection, objectColor, steps);

    } else {
        finalColor = calculateBackground(fragCoord, rayOrigin, rayDir);
    }

    finalColor = applyPostProcessing(finalColor, q);
    screenColor = vec4(finalColor, 1.0);


}





