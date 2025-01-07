#version 330 core


out vec4 screenColor;

//################ CAMERA UNIFORMs ################
uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;


//################ RAY MARCH UNIFORMS ################
uniform float MAX_DIST; //default 200.0
uniform int MAX_STEPS; //default 200
uniform float EPSILON; //default 0.0001
#define PHI 1.61803398874989484820459
uniform bool repeatFractal; //default false
uniform float repeatCellSize; //default 6.7

//################ SCENE UNIFORMS ################
uniform vec3 backgroundColour; //default vec3(0.4, 1.0, 1.0)
uniform bool useHalo; //default true
uniform bool useGradient; //default true
uniform float haloRadius; //default 17.0
uniform vec3 haloColour; //default vec3(1.0, 0.8, 0.4)
uniform vec3 fractalColour; //defaul vec3(0.0078, 0.0078, 0.0078);

//################ LIGHTING UNIFORMS ################
uniform vec3 ambientColor; //default vec3(0.9137, 0.9137, 0.9137)
uniform vec3 lightSourceDir; //default vec3(1.0f, 1.0f, 1.0f)

uniform float specularStrength; //default 0.5
uniform float shininess; //default 32.0

uniform bool ambientOcclusion; //default false
uniform bool softShadows; //default false


uniform int shadowMaxSteps; //default 100
uniform float kSoftShadow; //default 8.0
uniform float lightestShadow; //default 0.7
uniform float darkestShadow; //default 0.2

////################ GLOW UNIFORMS //################
uniform bool glowOn; //default true
uniform vec3 glowColor; //default vec3(1.0, 0.0, 0.0)
uniform float glowStrength; //default 0.5


//################ POST PROCESSING UNIFORMS ################
uniform float gammaAmount; //default 2.2
uniform float contrastAmount; //default 0.5 // (0.0 - 1.0)
uniform float saturationAmount; //default 1.0
uniform float vignetteAmount; //default 0.5 // (0.0 - 1.0)
uniform vec3 luminanceColour; //default vec3(0.2126, 0.7152, 0.0722)

//################ COLOURS UNIFORMS ################
uniform int colorMode; //default 0
uniform float positionColouringScale; //default 0.6
uniform vec3 positionColourOne; //default vec3(0.0, 1.0, 0.6667)
uniform vec3 positionColourTwo; //default vec3(0.149, 0.0196, 0.3882)

uniform float iterationColourVarOne; //default 0.4
uniform float iterationColourVarTwo; //default 2.0
uniform float iterationColourVarThree; //default 3.7
uniform vec3 iterationColourVarFour; //default vec3(0.4118, 0.6588, 0.702)

//################ TRANSFORMATION UNIFORMS ################
uniform bool useScale; //default false
uniform float scaleAmount; //default 2.0
uniform bool useTwist; //default false
uniform float twistAmount; //default 0.5
uniform bool useBend; //default false
uniform float bendAmount; //default 0.1
uniform bool useWarp; //default false
uniform float warpAmount; //default 0.0001









// #define FOV 35.0f


// //################ RAY MARCH UNIFORMS ################
// #define MAX_DIST 200.0
// #define MAX_STEPS 200
// #define EPSILON 0.0001
// #define PHI 1.61803398874989484820459
// #define repeatFractal false
// #define repeatCellSize 6.7

// //################ SCENE UNIFORMS ################
// #define backgroundColour vec3(0.0, 0.0, 0.0) // vec3(0.4, .6, 1.0)
// #define useHalo true
// #define useGradient true
// #define haloRadius 17.0
// #define haloColour vec3(1.0, 0.0, 0.0) //vec3(1.0, 0.8, 0.4)
// #define fractalColour vec3(0.0078, 0.0078, 0.0078)

//################ MENGERSPONGE UNIFORMS ################
#define mengerspongeIterations 6

//################ MANDELBULB UNIFORMS ################
//#define Power 8.0f
uniform float Power;
uniform float mandelbulbIterations;

// //################ LIGHTING UNIFORMS ################
// #define ambientColor vec3(0.9137, 0.9137, 0.9137)
// #define lightSourceDir vec3(1.0f, 1.0f, 1.0f)

// #define specularStrength 0.5
// #define shininess 32.0

// #define ambientOcclusion false
// #define softShadows false

// #define shadowMaxSteps 100
// #define kSoftShadow 8.0
// #define lightestShadow 0.7
// #define darkestShadow 0.2

// ////################ GLOW UNIFORMS //################
// #define glowOn true
// #define glowColor vec3(1.0, 0.0, 0.0)
// #define glowStrength 0.5


// //################ POST PROCESSING UNIFORMS ################
// #define gammaAmount 2.2
// #define contrastAmount 0.5 // 0.0 - 1.0
// #define saturationAmount 1.0
// #define vignetteAmount 0.5// 0.0 - 1.0
// #define luminanceColour vec3(0.2126, 0.7152, 0.0722)

// //################ COLOURS UNIFORMS ################
// uniform int colorMode;
// #define positionColouringScale 0.6
// #define positionColourOne vec3(0.0, 1.0, 0.6667)
// #define positionColourTwo vec3(0.149, 0.0196, 0.3882)

// #define iterationColourVarOne 0.4
// #define iterationColourVarTwo 2.0
// #define iterationColourVarThree 3.7
// #define iterationColourVarFour vec3(0.4118, 0.6588, 0.702)

// //################ TRANSFORMATION UNIFORMS ################
// #define useScale false
// #define scaleAmount 2.0
// #define useTwist false
// #define twistAmount 0.5
// #define useBend false
// #define bendAmount 0.1
// #define useWarp false
// #define warpAmount 0.0001




//##############################################################################################
//######################################## SDF UTILS ########################################
//##############################################################################################



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
//##################################### TRANSFORMATIONS ########################################
//##############################################################################################


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


//##############################################################################################
//##################################### FRACTAL SDFS ########################################
//##############################################################################################


vec2 mengerSpongeSDF(vec3 rayPos) {

    float cubeWidth = 1.5;
    const float oneThird = 1.0 / 3.0;
    float spongeCube = cubeSDF(rayPos, cubeWidth);
    float mengerSpongeDist = spongeCube;
    
    float scale = 1.0;
    int iterations = 0;
    float minDist = 1000.0;
    for(int i = 0; i < mengerspongeIterations; ++i) {

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
        
        if (mengerSpongeDist < minDist) {
            minDist = mengerSpongeDist;
            iterations = i;
        }

        scale *= 3.0;

    }
    float colorFactor = float(iterations) / mengerspongeIterations;
    return vec2(mengerSpongeDist, colorFactor);
}

vec3 estimateNormalMengerSponge(vec3 p) {

    vec2 dxDistAndColor = mengerSpongeSDF(p + vec3(EPSILON, 0.0, 0.0)) - mengerSpongeSDF(p - vec3(EPSILON, 0.0, 0.0));
    float dx = dxDistAndColor.x;

    vec2 dyDistAndColor = mengerSpongeSDF(p + vec3(0.0, EPSILON, 0.0)) - mengerSpongeSDF(p - vec3(0.0, EPSILON, 0.0));
    float dy = dyDistAndColor.x;

    vec2 dzDistAndColor = mengerSpongeSDF(p + vec3(0.0, 0.0, EPSILON)) - mengerSpongeSDF(p - vec3(0.0, 0.0, EPSILON));
    float dz = dzDistAndColor.x;

    return normalize(vec3(dx, dy, dz));
}



vec2 mandelbulbSDF(vec3 rayPos) {

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

vec3 estimateNormalMandelBulb(vec3 p) {
    vec2 dxDistAndColor = mandelbulbSDF(p + vec3(EPSILON, 0.0, 0.0)) - mandelbulbSDF(p - vec3(EPSILON, 0.0, 0.0));
    float dx = dxDistAndColor.x;

    vec2 dyDistAndColor = mandelbulbSDF(p + vec3(0.0, EPSILON, 0.0)) - mandelbulbSDF(p - vec3(0.0, EPSILON, 0.0));
    float dy = dyDistAndColor.x;

    vec2 dzDistAndColor = mandelbulbSDF(p + vec3(0.0, 0.0, EPSILON)) - mandelbulbSDF(p - vec3(0.0, 0.0, EPSILON));
    float dz = dzDistAndColor.x;

    return normalize(vec3(dx, dy, dz));
}


vec2 apollonianGasketSDF(vec3 p) {
    float distance = 0.0f;
    float colorFactor = 1.0f;
    return vec2(distance, colorFactor);
}


vec3 estimateNormalApollonianGasket(vec3 p) {
    vec2 dxDistAndColor = apollonianGasketSDF(p + vec3(EPSILON, 0.0, 0.0)) - apollonianGasketSDF(p - vec3(EPSILON, 0.0, 0.0));
    float dx = dxDistAndColor.x;

    vec2 dyDistAndColor = apollonianGasketSDF(p + vec3(0.0, EPSILON, 0.0)) - apollonianGasketSDF(p - vec3(0.0, EPSILON, 0.0));
    float dy = dyDistAndColor.x;

    vec2 dzDistAndColor = apollonianGasketSDF(p + vec3(0.0, 0.0, EPSILON)) - apollonianGasketSDF(p - vec3(0.0, 0.0, EPSILON));
    float dz = dzDistAndColor.x;

    return normalize(vec3(dx, dy, dz));
}


//##############################################################################################
//######################################### COLOUR #########################################
//##############################################################################################


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

    if (colorMode == 0) {
        color = fractalColour;
    } else if (colorMode == 1) {
        color = colorByNormal(normal);
    } else if (colorMode == 2) {
        color = colorByPosition(position);
    } else if (colorMode == 3) {
        color = colorByFractal(colorFactor);
    } else {
        color = fractalColour;
    }
    

    return color;
}





//##############################################################################################
//######################################### LIGHTING #########################################
//##############################################################################################


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



//##############################################################################################
//######################################### BACKGROUND #########################################
//##############################################################################################

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



//##############################################################################################
//###################################### POST PROCESSING #######################################
//##############################################################################################

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


//##############################################################################################
//######################################## RAY MARCHING ########################################
//##############################################################################################

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

        vec2 distAndColor = mandelbulbSDF(point);
        // vec2 distAndColor = mengerSpongeSDF(point);
        // vec2 distAndColor = apollonianGasketSDF(point);


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


//##############################################################################################
//######################################## MAIN ########################################
//##############################################################################################



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
        // vec3 normal = estimateNormalMengerSponge(hitPoint);
        vec3 normal = estimateNormalMandelBulb(hitPoint);
        // vec3 normal = estimateNormalApollonianGasket(hitPoint);

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






