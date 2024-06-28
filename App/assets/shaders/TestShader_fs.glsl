#version 330 

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform float uTime;
uniform vec2 uResolution;

vec3 CreateSpiral(vec2 uv)
{
    vec3 color = vec3(0.5f, 0.3f, 1.f);

    float d = length(uv);
    d -= 0.5f;
    d = sin(d * 10.f + uTime) / 12.f;
    d = abs(d);
    d = 0.025f / d; 

    color *= d;

    return color;
}

void main()
{
    vec2 uv = fragTexCoord * 2.f - 1.f;
    uv.x *= (uResolution.x / uResolution.y);

    vec3 color = CreateSpiral(uv);
    finalColor = vec4(color, 1.f);
}
