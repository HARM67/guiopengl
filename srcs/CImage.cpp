#include "CImage.hpp"
#include "CTexture.hpp"

CImage CImage::singleton;

CImage::CImage()
{
	p_graphic = CGraphic::Instance();
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
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

	m_shader_programme = CShader::create("CImage_shader", "./shaders/texture_vs.glsl", "./shaders/texture_fs.glsl");
	
	m_scr = glGetUniformLocation(m_shader_programme, "scr");
	m_pos = glGetUniformLocation(m_shader_programme, "pos");
	m_size = glGetUniformLocation(m_shader_programme, "size");
}

CImage::~CImage()
{

}
