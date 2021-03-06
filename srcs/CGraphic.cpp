#include "CGraphic.hpp"

CGraphic	CGraphic::m_instance=CGraphic();

CGraphic::CGraphic()
{
	width = 2400;
	height = 1200;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(width, height, "<--gui_Opengl-->", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	Init_surface();
	glClearColor(0.12f, 0.150f, 0.25f, 0.0f);
}

GLuint	CGraphic::get_vao()
{
	return (m_vao);
}

void	CGraphic::Init_surface()
{
	GLuint			m_text_co;
	GLuint			m_vbo;

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
}

CGraphic::~CGraphic()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

CGraphic	*CGraphic::Instance()
{
	return (&m_instance);
}
