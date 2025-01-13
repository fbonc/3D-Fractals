uniform float kleinianIterations; // 6


vec2 SDF(in vec3 pos)
{
    float scale = 1.0;

    for(int i = 0; i < int(kleinianIterations); i++)
    {

        //fold space [-1,1]
        pos = -1.0 + 2.0 * fract(0.5 * pos + 0.5);
        //push it slightly outward
        pos -= sign(pos) * 0.04;
        //compute r^2
        float r2 = dot(pos, pos);

        //inversesquareish scaling
        float k = 0.95 / r2;
        pos *= k;
        scale *= k;

    }

    //final shape is derived from two distances: d1 vs d2
    float d1  = sqrt(min(min(dot(pos.xy, pos.xy),
                             dot(pos.yz, pos.yz)),
                             dot(pos.zx, pos.zx))) - 0.02;
    float d2  = abs(pos.y);

    // pick whichever is smaller
    float dmi = d2;
    //adr becomes the pattern factor for color
    float adr = 0.7 * floor((0.5 * pos.y + 0.5) * 8.0);
    if(d1 < d2)
    {
        dmi = d1;
        //if we pick d1 , set adr=0 (removes stripes)
        adr = 0.0;
    }

    float distanceEstimate = 0.5 * dmi / scale;

    float colorFactor = adr;

    // Return them as (distance, colorFactor)
    return vec2(distanceEstimate, colorFactor);
}