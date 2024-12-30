#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;
layout (location = 2) in vec3 aColor;

out vec2 iTexCoord;
out vec3 iColor;

void main() {
	iTexCoord = aTexCoord.xy;
	iColor = aColor;
	gl_Position = vec4(aPos, 1.0);
}