float calculateSoftShadow(vec3 ro, vec3 rd, float k) {
    float res = 1.0;
    float t = 0.1;
    float maxDistance = MAX_DIST;

    for (int i = 0; i < shadowMaxSteps; i++) {
        vec3 currentPoint = ro + rd * t;

        // vec2 distAndColor = apollonianGasketSDF(currentPoint);
        // vec2 distAndColor = mengerSpongeSDF(currentPoint);
        vec2 distAndColor = mandelbulbSDF(currentPoint);
        float h = distAndColor.x;

        if (h < 0.001) {
            res = 0.0;
            break;
        }
        //accumulate minimum shadow factor
        res = min(res, k * h / t);
        t += clamp(h, 0.005, 0.1);
        if (t > maxDistance) {
            break;
        }
    }
    return clamp(res, darkestShadow, lightestShadow);
}



float calculateDiffuse(vec3 normal, vec3 lightDirection) {
    return max(dot(normal, lightDirection), 0.0);
}

float calculateSpecular(vec3 normal, vec3 viewDir, vec3 lightDirection, float shininessValue, float specularStrengthValue) {
    vec3 reflectDir = reflect(-lightDirection, normal);
    return pow(max(dot(viewDir, reflectDir), 0.0), shininess) * specularStrength;
}


vec3 calculateLighting(vec3 hitPoint, vec3 normal, vec3 viewDir, vec3 lightDirection, vec3 objectColor, int steps) {
    float diffuse = calculateDiffuse(normal, lightDirection);

    float specular = calculateSpecular(normal, viewDir, lightDirection, shininess, specularStrength);

    vec3 finalColor;

    float stepFactor = float(steps) / float(MAX_STEPS);

    float shadow = 1.0f;

    if (softShadows) {
        float k = kSoftShadow;
        shadow = calculateSoftShadow(hitPoint, lightDirection, k);
        finalColor = (ambientColor * objectColor * shadow) + (diffuse * objectColor + specular * vec3(1.0)) * shadow;
    } else {
        finalColor = objectColor;
    }

    if (ambientOcclusion){
        //no shadows, only ambient occlusion
        finalColor -= stepFactor;
    } else if (glowOn) {
        finalColor += glowColor * stepFactor * glowStrength;
    }

    return clamp(finalColor, 0.0, 1.0);
}
