#include "CTexture.hpp"

CTexture::t_texture	CTexture::list;

bool CTexture::load_texture (string file_name) {
	int n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load (file_name.c_str(), &width, &height, &n, force_channels);
	if (!image_data) {
		fprintf (stderr, "ERROR: could not load %s\n", file_name.c_str());
		return false;
	}
	if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0) {
		fprintf (
			stderr, "WARNING: texture %s is not power-of-2 dimensions\n", file_name.c_str()
		);
	}
	int width_in_bytes = width * 4;
	unsigned char *top = NULL;
	unsigned char *bottom = NULL;
	unsigned char temp = 0;
	int half_height = height / 2;

	for (int row = 0; row < half_height; row++) {
		top = image_data + row * width_in_bytes;
		bottom = image_data + (height - row - 1) * width_in_bytes;
		for (int col = 0; col < width_in_bytes; col++) {
			temp = *top;
			*top = *bottom;
			*bottom = temp;
			top++;
			bottom++;
		}
	}
	glGenTextures (1, &nbr);
	glActiveTexture (GL_TEXTURE0);
	glBindTexture (GL_TEXTURE_2D, nbr);
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	GLfloat max_aniso = 0.0f;
	return true;
}

int		CTexture::getWidth()
{
	return (width);
}

int		CTexture::getHeight()
{
	return (height);
}

void	CTexture::setSize(float v_width, float v_height)
{
	width	=	v_width;
	height	=	v_height;
}

void	CTexture::setSize(t_size size)
{
	width = size.width;
	height = size.height;
}

t_size	CTexture::getSize()
{
	t_size	rt;
	rt.width = width;
	rt.height = height;
	return (rt);
}
