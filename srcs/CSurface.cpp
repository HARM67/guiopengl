#include "CSurface.hpp"

CSurface::CSurface()
{

}

CSurface::~CSurface()
{

}

void	CSurface::Init()
{
	CGraphic	*graphic = CGraphic::Instance();

	GLuint vs, fs;
	GLuint shader_programme;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	GLfloat g_uv_buffer_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	GLfloat	points[] = {
		0.0f, 0.0f,  0.0f,
		1.0f, 0.0f,  0.0f,
		1.0f,  1.0f,  0.0f,
		1.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f, 0.0f,  0.0f
	};
	
	glGenBuffers (1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points,
			GL_STATIC_DRAW);

	GLuint	text_co;
	glGenBuffers (1, &text_co);
	glBindBuffer(GL_ARRAY_BUFFER, text_co);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), g_uv_buffer_data,
			GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, text_co);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//load_texture("lena.bmp", &img);
	printf("%u", img);
	char* vertex_shader =
	"#version 410\n"
	"uniform vec2 scr;"
	"uniform vec2 pos;"
	"uniform vec2 size;"
	"in vec3 vp;"
	"in vec2 tex;"
	"out vec2 UV;"
	"void main() {"
	"	gl_Position.x = ((((vp.x * size.x) + pos.x) / scr.x) - 1);"
	"	gl_Position.y = -((((vp.y * size.y) + pos.y) / scr.y) - 1);"
	"	gl_Position.z = 0.0;"
	"	gl_Position.w = 1.0;"
	"	UV.s = tex.s;"
	"	UV.t = -tex.t;"
	"}";

	char *fragment_shader =
		"#version 410\n"
		"uniform sampler2D myTextureSampler;"
		"in vec2 UV;"
		"out vec3 frag_colour;"
		"void main () {"
	"        frag_colour = texture( myTextureSampler, UV ).rgb;"
		"}";


	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram ();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram (shader_programme);

	GLuint	scr;
	scr = glGetUniformLocation(shader_programme, "scr");

	GLuint	pos;
	pos = glGetUniformLocation(shader_programme, "pos");
	
	GLuint	size;
	size = glGetUniformLocation(shader_programme, "size");
	while( glfwGetKey(graphic->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(graphic->m_window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (shader_programme);
		glUniform2f(scr, CGraphic::Instance()->width / 2.0f, CGraphic::Instance()->height / 2.0f);
		glUniform2f(pos, 100.0f, 100.0f);
		glUniform2f(size, 512.0f, 512.0f);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwPollEvents();
		glfwSwapBuffers(graphic->m_window);
	}
}

void	CSurface::render()
{

}
