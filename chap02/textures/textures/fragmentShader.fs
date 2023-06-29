#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord1;
in vec2 texCoord2;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, texCoord1), texture(texture2, texCoord2), 0.5);
}