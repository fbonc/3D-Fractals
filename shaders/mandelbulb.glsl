uniform float Power;
uniform int mandelbulbIterations; //default 40

vec2 SDF(vec3 rayPos) {

    vec3 currentPoint = rayPos;
    float radius;  //distance from the origin
    float derivative = 1.0;  //derivative used for distance estimation
    float minRadius = 1000.0;
    int iterations = 0;

    for (int i = 0; i < mandelbulbIterations; i++) {

        radius = length(currentPoint);
        if (radius > 4.0) break;  //early exit if outside the bounding radius

        if (radius < minRadius) {
            minRadius = radius;
            iterations = i;
        }

        //convert current point to polar coordinates
        float polarAngle = acos(currentPoint.z / radius);
        float azimuthalAngle = atan(currentPoint.y, currentPoint.x);
        
        derivative = pow(radius, Power - 1.0) * Power * derivative + 1.0;

        //scale and rotate the point based on the current radius and angles
        float scaledRadius = pow(radius, Power);
        polarAngle *= Power;
        azimuthalAngle *= Power;

        //convert back to cartesian coordinates
        currentPoint = scaledRadius * vec3(
            sin(polarAngle) * cos(azimuthalAngle),
            sin(azimuthalAngle) * sin(polarAngle),
            cos(polarAngle)
        );
        currentPoint += rayPos;

    }

    float de = 0.5 * log(radius) * radius / derivative;
    float colorFactor = float(iterations) /40.0;

    return vec2(de, colorFactor);  //final distance estimation

}

