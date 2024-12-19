#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uProj;
uniform mat4 uView;

out vec3 vColor;
out vec3 vPos;

void main()
{
  vPos = aPos;
	vColor = aColor;

	gl_Position = uProj * uView * vec4(aPos, 1.0);
}
