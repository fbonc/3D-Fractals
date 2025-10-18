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