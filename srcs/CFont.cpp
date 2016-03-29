#include "CFont.hpp"

CFont::t_font	CFont::list;

void	CFont::load()
{
	error = FT_Init_FreeType(&library);

	m_shader_programme = CShader::create("CTexte_shader", "./shaders/texte_vs.glsl", "./shaders/texte_fs.glsl");

	m_scr = glGetUniformLocation(m_shader_programme, "scr");
	m_pos = glGetUniformLocation(m_shader_programme, "pos");
	m_size = glGetUniformLocation(m_shader_programme, "size");
	m_color = glGetUniformLocation(m_shader_programme, "in_color");
}


void	CFont::print_all_slot()
{
	int i;

	i = 0;
	t_font2::iterator	it;
	for (it = char_font.begin(); it != char_font.end(); it++)
	{
		cout << "letter : " << (char)it->first << it->second->face->glyph->bitmap.width << " " << it->second->face->glyph->bitmap.rows << endl;
	}
}

void	CFont::load_char_font(unsigned int c)
{
	int	glyph_index;
	t_letter	*tmp = new t_letter;

	char_font.insert(pair<unsigned int, t_letter*>(c, tmp));
	error = FT_New_Face( library,
			font_name.c_str(),
			0,
			&tmp->face);
	error = FT_Set_Pixel_Sizes(
			tmp->face,
			0,   
			size);
	glyph_index = FT_Get_Char_Index(tmp->face, c);
	error = FT_Load_Glyph(
			tmp->face,        
			glyph_index,  
			FT_LOAD_DEFAULT); 
	error = FT_Render_Glyph( tmp->face->glyph,
			FT_RENDER_MODE_NORMAL); 

	FT_GlyphSlot	slot = tmp->face->glyph;
	glActiveTexture (GL_TEXTURE0);
	glGenTextures (1, &tmp->nbr);
	glBindTexture (GL_TEXTURE_2D, tmp->nbr);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RED,
		slot->bitmap.width,
		slot->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		slot->bitmap.buffer
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//cout << "letter : " << (char)c << tmp->slot->bitmap.width << " " << tmp->slot->bitmap.rows << endl;
	//print_all_slot();
}

FT_GlyphSlot	CFont::print_char(unsigned int	c, t_position pos, t_color color)
{
	t_font2::iterator it;
	
	it = char_font.find(c);
	if (it == char_font.end())
	{
		load_char_font(c);
		it = char_font.find(c);
	}
	FT_GlyphSlot	slot = it->second->face->glyph;
	glUseProgram (m_shader_programme);
	glUniform2f(m_scr, CGraphic::Instance()->width / 2.0f, CGraphic::Instance()->height / 2.0f);
	glUniform2f(m_pos, pos.x + slot->bitmap_left, pos.y - slot->bitmap_top + size);
	glUniform2f(m_size, slot->bitmap.width, slot->bitmap.rows);
	glBindVertexArray(CGraphic::Instance()->get_vao());
	glUniform4f(m_color, color.red, color.green, color.blue, color.alpha);
	glBindTexture (GL_TEXTURE_2D, it->second->nbr);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	return (slot);
}
