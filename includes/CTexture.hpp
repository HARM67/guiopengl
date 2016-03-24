#ifndef CTEXTURE_HPP
# define CTEXTURE_HPP
#define GLFW_INCLUDE_GLCOREARB
# include "s_type.h"
# include <iostream>
# include <string>
# include <map>
# include "stb_image.h"
# include <GLFW/glfw3.h>

using namespace std;

class			CTexture
{
private:
	typedef map <string, CTexture *>	t_texture;
	static	t_texture	list;
	GLuint		nbr;
	int	width;
	int	height;
	bool load_texture (string file_name);
	CTexture(){};
	~CTexture(){};
public:
	static GLuint	create_texture(string filename)
	{
		CTexture	*rt = new CTexture;
		rt->load_texture(filename.c_str());
		list.insert(pair<string, CTexture*>(filename, rt));
		return (rt->nbr);
	};
	static CTexture	*get_texture(string filename)
	{
		return (list.find(filename)->second);
	};
	int				getWidth();
	int				getHeight();
};
#endif
