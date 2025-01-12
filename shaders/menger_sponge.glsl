uniform float mengerSpongeIterations; //default 6


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



vec2 SDF(vec3 rayPos) {

    float cubeWidth = 1.5;
    const float oneThird = 1.0 / 3.0;
    float spongeCube = cubeSDF(rayPos, cubeWidth);
    float mengerSpongeDist = spongeCube;
    
    float scale = 1.0;
    int iterations = 0;
    float minDist = 1000.0;
    for(int i = 0; i < mengerSpongeIterations; ++i) {

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
    float colorFactor = float(iterations) / mengerSpongeIterations;
    return vec2(mengerSpongeDist, colorFactor);
}