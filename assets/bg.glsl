#version 330 core

out vec4 fragColor;

uniform vec2 uResolution;
uniform float uTime;

void main()
{
    vec2 uv = gl_FragCoord.xy / uResolution;
    uv *= 10.0;

    float v = sin(uv.x + uTime);
    v += sin(uv.y + uTime * 1.2);
    v += sin((uv.x + uv.y) * 0.5 + uTime * 0.7);

    v /= 3.0;
    v *= 10.0;
    v += 0.5;

    fragColor = vec4(v * sin(uTime), v * 0.1, v * 0.3, 1.0);
}