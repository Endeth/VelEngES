#version 300 es

layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

out vec4 verColor;

void main()
{
	gl_Position = vec4(vVertex, 1.0);
	verColor = vec4(vNormal, 1.0);
}