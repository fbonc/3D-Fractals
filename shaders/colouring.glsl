vec3 colorByNormal(vec3 normal) {
    return normal * 0.5 + 0.5; //map normals from [-1,1] to [0,1]
}

vec3 colorByPosition(vec3 position) {
    float factor = length(position) / (positionColouringScale);
    return mix(positionColourOne, positionColourTwo, factor); //this one is based on each point's distance from centre
}

vec3 colorByFractal(float colorFactor) { //fractal iterations
    colorFactor = pow(clamp(colorFactor, 0.0, 1.0), iterationColourVarOne);
    return 0.5 + 0.5 * sin(iterationColourVarTwo + iterationColourVarThree * colorFactor + iterationColourVarFour);
}


vec3 getColor(int steps, vec3 normal, vec3 position, float distance, float colorFactor) {
    vec3 color;

    if (colorMode == 0.0) {
        color = fractalColour;
    } else if (colorMode == 1.0) {
        color = colorByNormal(normal);
    } else if (colorMode == 2.0) {
        color = colorByPosition(position);
    } else if (colorMode == 3.0) {
        color = colorByFractal(colorFactor);
    } else {
        color = fractalColour;
    }
    

    return color;
}
