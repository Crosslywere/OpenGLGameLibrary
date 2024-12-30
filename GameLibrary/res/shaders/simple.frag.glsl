#version 330 core

in vec2 iTexCoord;
in vec3 iColor;

uniform vec3 color;
uniform sampler2D brickTexture;

void main() {
	vec4 tcol = texture(brickTexture, iTexCoord);
	vec3 fcol = tcol.xyz * color * iColor;
	gl_FragColor = vec4(fcol, 1.0);
}