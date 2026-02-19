#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 ourColor;
out vec2 ourTex;

uniform mat4 transform;

// ───────── uniforms ─────────
uniform float uTime;
uniform float uAmp;
uniform float uSpeed;
uniform vec3  uAxis;
uniform vec3  uOffset;

uniform bool uAnimate;
uniform int  uAnimType;
/*
    0  = none
    1  = sine
    2  = bounce
    3  = saw
    4  = triangle
    5  = circle
    6  = pulse
    7  = shake
    8  = ease in-out
    9  = spiral
*/

// ───────── helpers ─────────
float t()
{
    return uTime * uSpeed;
}

// ───────── animations ─────────

// Smooth sine (axis-based)
vec3 animSine()
{
    return uAxis * sin(t()) * uAmp;
}

// Bounce (always positive)
vec3 animBounce()
{
    return uAxis * abs(sin(t())) * uAmp;
}

// Sawtooth (constant speed)
vec3 animSaw()
{
    float v = fract(t()) * 2.0 - 1.0;
    return uAxis * v * uAmp;
}

// Triangle wave
vec3 animTriangle()
{
    float v = abs(fract(t() + 0.5) * 2.0 - 1.0) * 2.0 - 1.0;
    return uAxis * v * uAmp;
}

// Circle (XY plane)
vec3 animCircle()
{
    return vec3(
        cos(t()),
        sin(t()),
        0.0
    ) * uAmp;
}

// Pulse (in–out scaling feel)
vec3 animPulse()
{
    float v = sin(t()) * 0.5 + 0.5;
    return uAxis * v * uAmp;
}

// Shake / jitter
float hash(float x)
{
    return fract(sin(x) * 43758.5453);
}

vec3 animShake()
{
    float n = hash(t());
    return uAxis * (n * 2.0 - 1.0) * uAmp;
}

// Ease in–out (polished motion)
float easeInOut(float x)
{
    return x * x * (3.0 - 2.0 * x);
}

vec3 animEaseInOut()
{
    float x = fract(t());
    float v = easeInOut(x) * 2.0 - 1.0;
    return uAxis * v * uAmp;
}

// Spiral (circle + growth)
vec3 animSpiral()
{
    float r = fract(t()) * uAmp;
    return vec3(
        cos(t()),
        sin(t()),
        0.0
    ) * r;
}

// ───────── dispatcher ─────────
vec3 computeAnimationOffset()
{
    if (!uAnimate)
        return vec3(0.0);

    if (uAnimType == 1) return animSine();
    if (uAnimType == 2) return animBounce();
    if (uAnimType == 3) return animSaw();
    if (uAnimType == 4) return animTriangle();
    if (uAnimType == 5) return animCircle();
    if (uAnimType == 6) return animPulse();
    if (uAnimType == 7) return animShake();
    if (uAnimType == 8) return animEaseInOut();
    if (uAnimType == 9) return animSpiral();

    return vec3(0.0);
}

// ───────── main ─────────
void main()
{
    vec3 animOffset = computeAnimationOffset();
    gl_Position = transform * vec4(aPos + uOffset + animOffset, 1.0);
    ourColor = aColor;
    ourTex = aTex;
}