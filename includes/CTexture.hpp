#ifndef CTEXTURE_HPP
# define CTEXTURE_HPP
#define GLFW_INCLUDE_GLCOREARB
# include "s_type.h"
# include <iostream>
# include <string>
# include <map>
# include "s_type.h"
# include "stb_image.h"
#define GLFW_INCLUDE_GLCOREARB
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
	static GLuint	create(string filename)
	{
		CTexture	*rt = new CTexture;
		rt->load_texture(filename.c_str());
		list.insert(pair<string, CTexture*>(filename, rt));
		return (rt->nbr);
	};
	static CTexture	*get(string filename)
	{
		map<string, CTexture *>::iterator it;
		it = list.find(filename);
		if (it != list.end())
			return (it->second);
		else
			return (0);
	};
	static GLuint	auto_get(string filename)
	{
		map<string, CTexture *>::iterator it;
		it = list.find(filename);
		if (it != list.end())
			return (it->second->nbr);
		else
		{
			cout << "auto create texture "<< filename << endl;
			return (create(filename));
		}
	};
	static GLuint	auto_get(string filename, t_size *size)
	{
		CTexture	*rt;

		auto_get(filename);
		rt = get(filename);
		size->width = rt->width;
		size->height = rt->height;
		return (rt->nbr);
	};
	int				getWidth();
	int				getHeight();
	t_size			getSize();
	void			setSize(float v_width, float v_height);
	void			setSize(t_size size);
};
#endif
