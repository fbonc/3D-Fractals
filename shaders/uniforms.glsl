// //################ CAMERA UNIFORMs ################
// uniform vec3 cameraPos;
// uniform vec3 target;
// uniform vec2 resolution;
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

// //################ MENGERSPONGE UNIFORMS ################
// #define mengerspongeIterations 6

// //################ MANDELBULB UNIFORMS ################
// uniform float Power;
// #define mandelbulbIterations 40

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


//################ CAMERA UNIFORMS ################
uniform vec3 cameraPos;
uniform vec3 target;
uniform vec2 resolution;


//################ RAY MARCH UNIFORMS ################
uniform float MAX_DIST; //default 200.0
uniform float MAX_STEPS; //default 200
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


uniform float shadowMaxSteps; //default 100
uniform float kSoftShadow; //default 8.0
uniform float lightestShadow; //default 0.7
uniform float darkestShadow; //default 0.2



//################ POST PROCESSING UNIFORMS ################
uniform float gammaAmount; //default 2.2
uniform float contrastAmount; //default 0.5 // (0.0 - 1.0)
uniform float saturationAmount; //default 1.0
uniform float vignetteAmount; //default 0.5 // (0.0 - 1.0)
uniform vec3 luminanceColour; //default vec3(0.2126, 0.7152, 0.0722)

//################ COLOURS UNIFORMS ################
uniform float colorMode; //default 0
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