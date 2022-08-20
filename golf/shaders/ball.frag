#version 330 core

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D tex2D;

out vec4 FragColor;

void main()
{
	FragColor = texture(tex2D, TexCoord) * vertexColor;
}