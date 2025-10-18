uniform float juliaIterations;
//uniform vec4  juliaC;                 // e.g. vec4(0.32, 0.04, 0.12, -0.63)
uniform float juliaC1;
uniform float juliaC2;
uniform float juliaC3;
uniform float juliaC4;

vec4 qsqr(in vec4 q)
{
    return vec4(
        q.x*q.x - q.y*q.y - q.z*q.z - q.w*q.w,
        2.0 * q.x * q.y,
        2.0 * q.x * q.z,
        2.0 * q.x * q.w
    );
}

float qlength2(in vec4 q)
{
    return dot(q,q);
}


vec2 SDF(in vec3 rayPos)
{
    vec4 z = vec4(rayPos, 0.0);
    vec4 juliaC = vec4(juliaC1, juliaC2, juliaC3, juliaC4);

    float md2 = 1.0;        
    float mz2 = dot(z, z);  

    float minRadius = 1e6;
    int bestIter  = 0;

    float iterationCounter = 0.0;
    for(int i = 0; i < int(juliaIterations); i++)
    {
        if(mz2 > 16.0) break;  

        float radius = sqrt(mz2);
        if (radius < minRadius) 
        {
            minRadius = radius;
            bestIter = i;
        }

        md2 *= 4.0 * mz2;

        z   = qsqr(z) + juliaC;
        mz2 = qlength2(z);

        iterationCounter++;
    }

    float distanceEstimate = 0.25 * sqrt(mz2 / md2) * log(mz2);

    float colorFactor = float(bestIter) / max(1.0, juliaIterations);

    return vec2(distanceEstimate, colorFactor);
}