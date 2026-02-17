#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTex;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;
uniform bool uUseTexture;

void main()
{
    if (uUseTexture)
    {
        vec4 tex1 = texture(uTexture, ourTex);
        vec4 tex2 = texture(uTexture2, ourTex);

        FragColor = mix(tex1, tex2, 0.5) * vec4(ourColor, 1.0);
    }
    else
        FragColor = vec4(ourColor, 1.0);
}