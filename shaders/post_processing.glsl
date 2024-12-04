vec3 applyPostProcessing(vec3 color, vec2 q) {
    //gamma Correction
    color = pow(clamp(color, 0.0, 1.0), vec3(1.0/gammaAmount));

    //contrast
    vec3 enhancedColor = color * color * (3.0 - 2.0 * color);
    color = mix(color, enhancedColor, contrastAmount);

    //saturation
    float luminance = dot(color, luminanceColour);
    vec3 grayscaleColor = vec3(luminance);
    color = mix(grayscaleColor, color, saturationAmount);

    //vignetting
    float vignetteFactor = pow(16.0 * q.x * q.y * (1.0 - q.x) * (1.0 - q.y), 0.7);
    float vignette = mix(1.0, vignetteFactor, vignetteAmount);
    color *= vignette;

    return color;
}