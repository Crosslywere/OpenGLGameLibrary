#version 330 core

in vec2 iTexCoord;
in vec3 iColor;

uniform vec3 color;

void main() {
	vec3 fcol = color * iColor;
	gl_FragColor = vec4(fcol, 1.0);
}