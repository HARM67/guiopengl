#version 410
uniform sampler2D myTextureSampler;
in vec2 UV;
out vec3 frag_colour;
void main () {
	frag_colour = texture( myTextureSampler, UV ).rgb;
}
