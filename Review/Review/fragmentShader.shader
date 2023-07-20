#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D containerTexture;
uniform sampler2D smileTexture;

void main()
{
	FragColor = mix(texture(containerTexture, TexCoord), texture(smileTexture, TexCoord), .2) * ourColor;
}