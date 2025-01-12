uniform float mandelboxIterations; // 10
uniform float foldingLimit; // 1.0
uniform float minRadius2; //0.5
uniform float fixedRadius2; //1.0
uniform float mbScale; //-1.5


void boxFold(inout vec3 z, inout float dr)
{
    if (z.x >  foldingLimit) z.x =  2.0*foldingLimit - z.x;
    else if (z.x < -foldingLimit) z.x = -2.0*foldingLimit - z.x;

    if (z.y >  foldingLimit) z.y =  2.0*foldingLimit - z.y;
    else if (z.y < -foldingLimit) z.y = -2.0*foldingLimit - z.y;

    if (z.z >  foldingLimit) z.z =  2.0*foldingLimit - z.z;
    else if (z.z < -foldingLimit) z.z = -2.0*foldingLimit - z.z;
}


void sphereFold(inout vec3 z, inout float dr)
{
    float r2 = dot(z, z);

    if (r2 < minRadius2)
    {
        //push outward if below min radius
        float factor = (fixedRadius2 / minRadius2);
        z  *= factor;
        dr *= factor;
    }
    else if (r2 < fixedRadius2)
    {
        //push inward if inside the big sphere
        float factor = (fixedRadius2 / r2);
        z  *= factor;
        dr *= factor;
    }
}


vec2 SDF(in vec3 rayPos)
{
    vec3 offset = rayPos;

    float dr = 1.0;   //derivative factor
    vec3  z  = rayPos;
    float iterationAccum = 0.0;

    for (int i = 0; i < int(mandelboxIterations); i++)
    {
        boxFold(z, dr);

        sphereFold(z, dr);

        z = z * mbScale + offset;

        dr = dr * abs(mbScale) + 1.0;

        iterationAccum += 1.0;
    }

    float r = length(z);
    float distanceEstimate = r / abs(dr);

    float colorFactor = iterationAccum / max(1.0, mandelboxIterations);

    return vec2(distanceEstimate, colorFactor);
}