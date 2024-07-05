#version 330 

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform float uTime;
uniform vec2 uResolution;
uniform vec3 uColorFactor;

#define PI 3.14f
#define NUM_LAYERS 6

vec3 CreateAxis(vec2 uv)
{
    vec3 color = vec3(0.f);
    float thickness = 1.f / uResolution.y;

    if (abs(uv.x) < thickness) color.g = 1.f;
    if (abs(uv.y) < thickness) color.r = 1.f;

    return color;
}

mat2 Rotate(float a)
{
    float s = sin(a);
    float c = cos(a);

    return mat2(c, -s, s, c);
}

float Hash21(vec2 uv)
{
    uv = fract(uv * vec2(123.34f, 456.21f));
    uv += dot(uv, uv + 45.32f);
    return fract(uv.x * uv.y);
}

float CreateStar(vec2 uv, float flare)
{
    float d = length(uv);
    float m = 0.05f / d;
    float rays = max(0.f, 1.f - abs(uv.x * uv.y * 1000.f));

    m += rays * flare;
    uv *= Rotate(PI/4.f);
    rays = max(0.f, 1.f - abs(uv.x * uv.y * 1000.f));
    m += rays * 0.3f * flare;

    m *= smoothstep(1.f, 0.2f, d);

    return m;
}

vec3 CreateStarLayer(vec2 uv)
{
    vec3 color = vec3(0.f);

    vec2 gv = fract(uv) - 0.5f;
    vec2 id = floor(uv);

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            vec2 offset = vec2(j, i);
            float n = Hash21(id + offset);
            float size = fract(n * 345.32f);
            float star = CreateStar(gv - offset - vec2(n, fract(n * 34.f)) + 0.5f, smoothstep(0.85f, 1.f, size) * 0.7f);
            vec3 c = sin(vec3(0.2f, 0.3f, 0.8f) * fract(n * 2345.f) * 123.f) * 0.5f + 0.5f;
            c *= vec3(uColorFactor.xy, uColorFactor.z + size);

            color += star * size * c;
        }
    }

    return color;
}

void main()
{
    vec2 uv = fragTexCoord * 2 - 1.f;
    uv.x *= (uResolution.x / uResolution.y);

    vec3 color = vec3(0.f);

    for (float i = 0; i < 1.f; i += 1.f / NUM_LAYERS)
    {
        float depth = fract(i + (uTime * 0.03f));
        float scale = mix(10.f, 0.5f, depth);
        color += CreateStarLayer(uv * scale + i * 253.f) * depth; 
    }

    finalColor = vec4(color, 1.f);
}
