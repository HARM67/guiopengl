#include "CImage.hpp"
#include "CTexture.hpp"

CImage::CImage()
{
	p_graphic = CGraphic::Instance();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLfloat uv_data[] = {
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
	glGenBuffers (1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points,
			GL_STATIC_DRAW);
	glGenBuffers (1, &m_text_co);
	glBindBuffer(GL_ARRAY_BUFFER, m_text_co);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), uv_data,
			GL_STATIC_DRAW);

	glGenVertexArrays (1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, m_text_co);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	m_img2 = CTexture::create_texture("2007BMP.jpg");
	m_img = CTexture::create_texture("lena.bmp");
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

	m_vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (m_vs, 1, &vertex_shader, NULL);
	glCompileShader(m_vs);

	m_fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fs, 1, &fragment_shader, NULL);
	glCompileShader(m_fs);

	m_shader_programme = glCreateProgram ();
	glAttachShader(m_shader_programme, m_fs);
	glAttachShader(m_shader_programme, m_vs);
	glLinkProgram (m_shader_programme);

	m_scr = glGetUniformLocation(m_shader_programme, "scr");
	m_pos = glGetUniformLocation(m_shader_programme, "pos");
	m_size = glGetUniformLocation(m_shader_programme, "size");
}

void	CImage::draw_Image(t_position pos, t_size size, GLuint img)
{
	glUseProgram (m_shader_programme);
	glUniform2f(m_scr, p_graphic->width / 2.0f, p_graphic->height / 2.0f);
	glUniform2f(m_pos, pos.x, pos.y);
	glUniform2f(m_size, size.width, size.height);
	glBindVertexArray(m_vao);
	glBindTexture (GL_TEXTURE_2D, m_img2);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

CImage::~CImage()
{

}
