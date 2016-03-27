#version 410
uniform vec2 scr;
uniform vec2 pos;
uniform vec2 size;
in vec3 vp;
in vec2 tex;
out vec2 UV;
void main() {
	gl_Position.x = ((((vp.x * size.x) + pos.x) / scr.x) - 1);
	gl_Position.y = -((((vp.y * size.y) + pos.y) / scr.y) - 1);
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	UV.s = tex.s;
	UV.t = tex.t;
}
