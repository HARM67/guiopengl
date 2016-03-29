#ifndef	CAUI_LOADER_HPP
# define	CAUI_LOADER_HPP
# include "CAui.hpp"
# include <string>
# include <vector>
# include <map>
# include <stdio.h>
# include <string.h>

using namespace std;

typedef map<string, string>	t_key;
typedef vector<CAui*>	t_child;

class	CAui_loader
{
public:
	CAui_loader();
	~CAui_loader();

	static CAui	*parse_object_rec(FILE *file)
	{
		CAui			*rt;
		t_key			key;
		t_child			child;
		char			buffer[2];
		int				token;
		char			lvalue[256];
		char			rvalue[2048];

		token = 0;
		bzero(lvalue, 256);
		bzero(rvalue, 2048);
		buffer[1] = 0;

		while (fread (buffer, 1, 1, file) > 0)
		{	
			if (token == 0)
			{
				if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t')
					continue;
				else if (*buffer == '"')
					token = 11;
				else
				{
					token = 1;
					strcat((char*)lvalue, buffer);
				}
			}
			else if (token == 1)
			{
				if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == ':')
				{
					token = 2;
					continue;
				}
				strcat((char*)lvalue, buffer);
			}
			else if (token == 2)
			{
				if (*buffer == ':')
					token = 3;
			}
			else if (token == 3)
			{
				if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t')
					continue;
				else if (*buffer == '"')
					token = 14;
				else if (*buffer == '{')
				{
					if ((strcmp("child", lvalue) == 0) || strcmp("\"child\"", lvalue) == 0)
					{
						child.push_back(parse_object_rec(file));
					}
					bzero(lvalue, 256);
					bzero(rvalue, 2048);
					token = 5;
				}
				else
				{
					token = 4;
					strcat((char*)rvalue, buffer);
				}
			}
			else if (token == 4)
			{
				if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t' || *buffer == ',')
				{
					key.insert(pair<string, string>(lvalue, rvalue));
					bzero(lvalue, 256);
					bzero(rvalue, 2048);
					if (*buffer == ',')
						token = 0;
					else
						token = 5;
					continue;
				}
				strcat((char*)rvalue, buffer);
			}
			else if (token == 5)
			{
				if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t')
					continue;
				else if (*buffer == ',' || *buffer == '}')
				{
					token = 0;
					if (*buffer == '}')
						break ;
				}
			}
		}
		if (token == 0)
			return (decode(&key, &child));
		return (0);
	};
	static CAui	*parse_object(string filename)
	{
		CAui	*rt;
		FILE	*file;
		unsigned char	buffer;

		file = fopen(filename.c_str(), "rb");
		while (fread (&buffer, 1, 1, file) > 0)
		{
			if (buffer == ' ' || buffer == '\n' || buffer == '\t')
				continue;
			if (buffer == '{')
			{
				break ;
			}
		}
		rt = parse_object_rec(file);
		fclose(file);
		return (rt);
	};
	
	static CAui	*decode(t_key *key, t_child *child)
	{
		float	tmp1;
		float	tmp2;
		CAui	*rt;

		t_key::iterator	it;
		it = key->find("name");
		if (it != key->end())
			rt = CAui::create(it->second);
		else
			return (0);

		tmp1 = rt->pos.x;
		tmp2 = rt->pos.y;
		it = key->find("pos_x");
		if (it != key->end())
			tmp1 = stoi(it->second);
		it = key->find("pos_y");
		if (it != key->end())
			tmp2 = stoi(it->second);
		rt->pos.x = tmp1;
		rt->pos.y = tmp2;

		tmp1 = rt->size.width;
		tmp2 = rt->size.height;
		it = key->find("width");
		if (it != key->end())
			tmp1 = stoi(it->second);
		it = key->find("height");
		if (it != key->end())
			tmp2 = stoi(it->second);
		rt->size.width = tmp1;
		rt->size.height = tmp2;

		it = key->find("str");
		if (it != key->end())
			rt->set_str(it->second);

		rt->content = *child;
		return (rt);
	};
};
#endif


