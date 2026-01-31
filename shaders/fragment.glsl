#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTex;

uniform sampler2D uTexture;
uniform bool uUseTexture;

void main()
{
    if (uUseTexture)
        FragColor = texture(uTexture, ourTex) * vec4(ourColor, 1.0);
    else
        FragColor = vec4(ourColor, 1.0);
}