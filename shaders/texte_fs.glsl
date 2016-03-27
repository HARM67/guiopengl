#version 410
uniform sampler2D myTextureSampler;
uniform vec4 in_color;
in vec2 UV;
out vec4 frag_colour;
void main () {
	frag_colour = vec4(1, 1, 1, texture( myTextureSampler, UV ).r) * in_color;
}
