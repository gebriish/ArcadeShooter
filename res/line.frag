#version 410 core

uniform vec3 uCamPos;

in vec3 vColor;
in vec3 vPos;

out vec4 FragColor;

void main()
{
	FragColor =  vec4(vColor, exp(-pow(length(vPos - uCamPos)/5.0, 2.0)));
}
