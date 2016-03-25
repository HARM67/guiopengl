#version 410
uniform sampler2D myTextureSampler;
in vec2 UV;
out vec4 frag_colour;
void main () {
	frag_colour = vec4(texture( myTextureSampler, UV ).rgb, 0.9);
}
