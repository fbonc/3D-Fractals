vec3 calculateBgColor (vec2 fragCoord) {
    vec2 q = fragCoord.xy / resolution.xy;
    vec2 uv = -1.0 + 2.0 * q;
    uv.x *= resolution.x / resolution.y;
    
    return exp(uv.y - 2.0) * backgroundColour;
}

vec3 calculateHaloColor(vec3 rayOrigin, vec3 rayDir) {
    vec3 forward = normalize(target - cameraPos);
    float halo = clamp(dot(normalize(-rayOrigin), rayDir), 0.0, 1.0);
    return haloColour * pow(halo, haloRadius);
}


vec3 calculateBackground(vec2 fragCoord, vec3 rayOrigin, vec3 rayDir) {

    vec3 bgColor = vec3(0.0f, 0.0f, 0.0f);
    vec3 haloColor = vec3(0.0f, 0.0f, 0.0f);

    bool baseBg = true;
    if (useGradient) {
        baseBg = false;
        bgColor = calculateBgColor(fragCoord);
    }
            
    if (useHalo) {
        baseBg = false;
        haloColor = calculateHaloColor(rayOrigin, rayDir);
    }

    vec3 finalBgColor;

    if(!baseBg) {
        finalBgColor = bgColor + haloColor;
    } else {
        finalBgColor = backgroundColour;
    }

    return vec3(finalBgColor);


}