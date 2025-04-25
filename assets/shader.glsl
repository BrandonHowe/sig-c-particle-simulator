#version 330 core

out vec4 fragColor;

uniform vec2 uResolution;

void main()
{
    vec2 uv = gl_FragCoord.xy / uResolution; // between 0 and 1

    float r = uv.x;
    float g = uv.y;
    float b = 0.5;

    fragColor = vec4(r, g, b, 1.0);
}