#include "CImage.hpp"
#include "CTexture.hpp"

CImage CImage::singleton;

CImage::CImage()
{
	p_graphic = CGraphic::Instance();
	//glEnable(GL_DEPTH_TEST);


	//glDepthFunc(GL_LESS);

	m_shader_programme = CShader::create("CImage_shader", "./shaders/texture_vs.glsl", "./shaders/texture_fs.glsl");
	
	m_scr = glGetUniformLocation(m_shader_programme, "scr");
	m_pos = glGetUniformLocation(m_shader_programme, "pos");
	m_size = glGetUniformLocation(m_shader_programme, "size");
	m_color = glGetUniformLocation(m_shader_programme, "in_color");
}

CImage::~CImage()
{

}
