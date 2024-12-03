#version 330 core


out vec4 screenColor;

//CAMERA UNIFORMs
uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;
#define FOV 35.0f


//RAY MARCH UNIFORMS
#define MAX_DIST 200.0
#define MAX_STEPS 200
#define EPSILON 0.0001
#define PHI 1.61803398874989484820459

//SCENE UNIFORMS
#define backGroundColour vec4(0.2, 0.81, 0.89, 1.0)
#define fractalColour vec3(0.9059, 0.9373, 0.9412)

//MENGERSPONGE UNIFORMS
#define numIters 6
#define widthOfCube 10.0

//MANDELBULB UNIFORMS
uniform float Power;
#define mandelBulbRadius 1.0

//LIGHTING UNIFORMS
#define specularStrength 0.5
#define shininess 32.0
#define kSoftShadow 8.0
#define ambientColor vec3(0.9137, 0.9137, 0.9137)
#define lightSourceDir vec3(1.0f, 1.0f, 1.0f)
#define shadowMaxSteps 100


#define ambientOcclusion true
#define softShadows true





float cubeSDF(vec3 rayPos, float width) {
  //half initial scale of square (arbitrary)
    float halfWidth = width / 2.0;
    vec3 corner = vec3(halfWidth, halfWidth, halfWidth);

    //fold ray into positive octant
    vec3 foldedPos = abs(rayPos);
    //corner to ray
    vec3 ctr = foldedPos - corner;

    //ignore negative components for outside points
    vec3 closestToOutsideRay = max(ctr, 0.0);

    float cornerToRayMaxComponent = max(max(ctr.x, ctr.y), ctr.z);
    float distToInsideRay = min(cornerToRayMaxComponent, 0.0);

    // return either the distance to outside OR distance to inside
    return length(closestToOutsideRay) + distToInsideRay;
} 



float sdCross(vec3 rayPos, float width) {
    float halfWidth = width / 2.0;
    vec3 corner = vec3(halfWidth, halfWidth, halfWidth);
    vec3 foldedPos = abs(rayPos);

    //corner to ray
    vec3 ctr = foldedPos - corner;

    float minComp = min(min(ctr.x, ctr.y), ctr.z);
    float maxComp = max(max(ctr.x, ctr.y), ctr.z);

    //acquire middle component
    float midComp = ctr.x + ctr.y + ctr.z - minComp - maxComp;

    vec2 closestOutsidePoint = max(vec2(minComp, midComp), 0.0);
    vec2 closestInsidePoint = min(vec2(midComp, maxComp), 0.0);

    // return either the distance to inside OR outside
    return length(closestOutsidePoint) + -length(closestInsidePoint);
}


//##############################################################################################
//######################################## PERLIN NOISE ########################################
//##############################################################################################


// Hash function to generate pseudo-random gradients
vec3 permute(vec3 x) {
    return mod(((x * 34.0) + 1.0) * x, 289.0);
}

// Fade function for smooth interpolation
vec3 fade(vec3 t) {
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

// 3D Perlin Noise function
float noise(vec3 P) {
    vec3 Pi = mod(floor(P), 289.0);
    vec3 Pf = fract(P);

    vec3 F = fade(Pf);

    // Generate gradient indices
    float aaa = dot(Pi, vec3(1.0, 57.0, 113.0));
    float aba = dot(Pi + vec3(0.0, 1.0, 0.0), vec3(1.0, 57.0, 113.0));
    float aab = dot(Pi + vec3(0.0, 0.0, 1.0), vec3(1.0, 57.0, 113.0));
    float abb = dot(Pi + vec3(0.0, 1.0, 1.0), vec3(1.0, 57.0, 113.0));
    float baa = dot(Pi + vec3(1.0, 0.0, 0.0), vec3(1.0, 57.0, 113.0));
    float bba = dot(Pi + vec3(1.0, 1.0, 0.0), vec3(1.0, 57.0, 113.0));
    float bab = dot(Pi + vec3(1.0, 0.0, 1.0), vec3(1.0, 57.0, 113.0));
    float bbb = dot(Pi + vec3(1.0, 1.0, 1.0), vec3(1.0, 57.0, 113.0));

    // Hash gradients
    vec3 g000 = permute(permute(permute(Pi)));
    vec3 g001 = permute(permute(permute(Pi + vec3(0.0, 0.0, 1.0))));
    vec3 g010 = permute(permute(permute(Pi + vec3(0.0, 1.0, 0.0))));
    vec3 g011 = permute(permute(permute(Pi + vec3(0.0, 1.0, 1.0))));
    vec3 g100 = permute(permute(permute(Pi + vec3(1.0, 0.0, 0.0))));
    vec3 g101 = permute(permute(permute(Pi + vec3(1.0, 0.0, 1.0))));
    vec3 g110 = permute(permute(permute(Pi + vec3(1.0, 1.0, 0.0))));
    vec3 g111 = permute(permute(permute(Pi + vec3(1.0, 1.0, 1.0))));

    // Compute gradients
    vec3 P0 = Pf;
    vec3 P1 = Pf - vec3(0.0, 1.0, 0.0);
    vec3 P2 = Pf - vec3(1.0, 0.0, 0.0);
    vec3 P3 = Pf - vec3(1.0, 1.0, 0.0);
    vec3 P4 = Pf - vec3(0.0, 0.0, 1.0);
    vec3 P5 = Pf - vec3(0.0, 1.0, 1.0);
    vec3 P6 = Pf - vec3(1.0, 0.0, 1.0);
    vec3 P7 = Pf - vec3(1.0, 1.0, 1.0);

    // Compute dot products
    float n000 = dot(P0, g000);
    float n100 = dot(P2, g100);
    float n010 = dot(P1, g010);
    float n110 = dot(P3, g110);
    float n001 = dot(P4, g001);
    float n101 = dot(P6, g101);
    float n011 = dot(P5, g011);
    float n111 = dot(P7, g111);

    // Interpolate
    vec3 nxy0 = mix(vec3(n000, n100, n010), vec3(n001, n101, n011), F.z);
    vec2 nx0 = mix(nxy0.xy, nxy0.yz, F.y);
    float n0 = mix(nx0.x, nx0.y, F.x);

    vec3 nxy1 = mix(vec3(n110, n110, n110), vec3(n111, n111, n111), F.z);
    vec2 nx1 = mix(nxy1.xy, nxy1.yz, F.y);
    float n1 = mix(nx1.x, nx1.y, F.x);

    // Final noise value
    return mix(n0, n1, F.x);
}

//##############################################################################################
//##############################################################################################
//##############################################################################################




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

vec3 warp(vec3 p) {
    float strength = 0.0001;
    p += strength * vec3(
        noise(p + vec3(0.0)),
        noise(p + vec3(100.0)),
        noise(p + vec3(200.0))
    );
    return p;
}

float mengerSpongeSDF(vec3 rayPos, int numIterations, float cubeWidth) {

    //############################### TRANSFORMATIONS #####################################
    //BEND
    // float bendAmount = 0.5;
    // rayPos = bend(rayPos, bendAmount);


    //TWIST
    // rayPos = twist(rayPos, 0.1);



    //WARP
    // rayPos = warp(rayPos);


    //####################################################################


    const float oneThird = 1.0 / 3.0;
    float spongeCube = cubeSDF(rayPos, cubeWidth);
    float mengerSpongeDist = spongeCube;
    
    float scale = 1.0;
    for(int i = 0; i < numIterations; ++i) {

        //determine repeated box width
        float boxedWidth = cubeWidth / scale;
        
        float translation = -boxedWidth / 2.0;
        vec3 ray = rayPos - translation;
        vec3 repeatedPos = mod(ray, boxedWidth);
        repeatedPos += translation;
        
        //scale coordinate systems from 
        //[-1/scale, 1/scale) -> to [-1.0, 1.0)
        repeatedPos *= scale;
        
        float crossesDist = sdCross(repeatedPos / oneThird, cubeWidth) * oneThird;
        
        //acquire actual distance by un-stretching
        crossesDist /= scale;
        
        mengerSpongeDist = max(mengerSpongeDist, -crossesDist);
        
        scale *= 3.0;
    }
    return mengerSpongeDist;
}

vec3 estimateNormalMengerSponge(vec3 p, int numIterations, float cubeWidth) {
    const float eps = 0.0001;

    float dx = mengerSpongeSDF(p + vec3(eps, 0.0, 0.0), numIterations, cubeWidth) - mengerSpongeSDF(p - vec3(eps, 0.0, 0.0), numIterations, cubeWidth);
    float dy = mengerSpongeSDF(p + vec3(0.0, eps, 0.0), numIterations, cubeWidth) - mengerSpongeSDF(p - vec3(0.0, eps, 0.0), numIterations, cubeWidth);
    float dz = mengerSpongeSDF(p + vec3(0.0, 0.0, eps), numIterations, cubeWidth) - mengerSpongeSDF(p - vec3(0.0, 0.0, eps), numIterations, cubeWidth);

    return normalize(vec3(dx, dy, dz));
}



float mandelbulbSDF(vec3 rayPos) {

    vec3 currentPoint = rayPos;
    float radius = mandelBulbRadius;  //distance from the origin
    float derivative = 1.0;  //derivative used for distance estimation

    for (int i = 0; i < 40; i++) {

        radius = length(currentPoint);
        if (radius > 4.0) break;  //early exit if outside the bounding radius

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

    return 0.5 * log(radius) * radius / derivative;  //final distance estimation

}

vec3 estimateNormalMandelBulb(vec3 p) {
    const float eps = 0.0001;
    float dx = mandelbulbSDF(p + vec3(eps, 0.0, 0.0)) - mandelbulbSDF(p - vec3(eps, 0.0, 0.0));
    float dy = mandelbulbSDF(p + vec3(0.0, eps, 0.0)) - mandelbulbSDF(p - vec3(0.0, eps, 0.0));
    float dz = mandelbulbSDF(p + vec3(0.0, 0.0, eps)) - mandelbulbSDF(p - vec3(0.0, 0.0, eps));
    return normalize(vec3(dx, dy, dz));
}


float sphereSDF(vec3 rayPos, vec3 center, float radius) {

    return length(rayPos - center) - radius;

}



vec3 repeat(vec3 rayPos, vec3 cell_width) {

    return mod(rayPos + 0.5 * cell_width, cell_width) - 0.5 * cell_width; //repeat space in all directions

}



//##############################################################################################
//######################################### LIGHTING #########################################
//##############################################################################################


float calculateSoftShadow(vec3 ro, vec3 rd, int numIterations, float cubeWidth, float k) {
    float res = 1.0;
    float t = 0.1;
    float maxDistance = MAX_DIST;

    for (int i = 0; i < shadowMaxSteps; i++) {
        vec3 currentPoint = ro + rd * t;
        float h = mengerSpongeSDF(currentPoint, numIterations, cubeWidth);
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
    return clamp(res, 0.09, 1.0);
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

    vec3 finalAmbientColor = ambientColor;

    float shadow = 1.0f;
    if (softShadows) {
        float k = kSoftShadow;
        shadow = calculateSoftShadow(hitPoint, lightDirection, numIters, widthOfCube, k);
    }

    vec3 finalColor;

    float colorFactor = float(steps) / float(MAX_STEPS);

    if (softShadows) {
        finalColor = (finalAmbientColor * objectColor * shadow) + (diffuse * objectColor + specular * vec3(1.0)) * shadow;
        finalColor = finalColor - colorFactor;
    } else if (ambientOcclusion){
        //no shadows, only ambient occlusion
        float colorFactor = float(steps) / float(MAX_STEPS);
        finalColor = objectColor - colorFactor;
    } else {
        finalColor = objectColor;
    }

    return clamp(finalColor, 0.0, 1.0);
}



//##############################################################################################
//#############################################################################################
//##############################################################################################


vec3 ray_direction(float fov, vec2 fragCoord, vec2 resolution, vec3 cameraPos, vec3 target) {
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



float ray_march(vec3 rayOrigin, vec3 rayDir, out int steps, out vec3 hitPoint) {

    float totalDist = 0.0;

    steps = 0;

    for (int i = 0; i < MAX_STEPS; i++) {

        steps += 1;
        vec3 point = rayOrigin + rayDir * abs(totalDist);

        //vec3 repeatedPoint = repeat(point, vec3(6.7)); //repeat object infinitely in all directions
        float dist = mengerSpongeSDF(point, numIters, widthOfCube);
        // float dist = mengerSpongeSDF(point, 7, 10);


        if (abs(dist) < EPSILON) {
            hitPoint = point;
            return totalDist;
        }
        
        totalDist += dist;

        if (totalDist > MAX_DIST) break;
        
    }

    return totalDist; //no hit

}



void main() {
    vec2 fragCoord = gl_FragCoord.xy;
    vec2 res = vec2(resolution.x, resolution.y);

    vec3 rayDir = ray_direction(FOV, fragCoord, res, cameraPos, target);
    vec3 rayOrigin = cameraPos;

    vec3 hitPoint;
    int steps;
    float distance = ray_march(rayOrigin, rayDir, steps, hitPoint);

    vec3 lightDir = normalize(lightSourceDir);

    if (distance < MAX_DIST) {
        vec3 normal = estimateNormalMengerSponge(hitPoint, numIters, widthOfCube);

        vec3 viewDir = normalize(cameraPos - hitPoint);

        vec3 lightDirection = normalize(lightDir);

        vec3 finalColor = calculateLighting(hitPoint, normal, viewDir, lightDirection, fractalColour, steps);

        screenColor = vec4(finalColor, 1.0);
    } else {
        screenColor = backGroundColour;
    }
}






