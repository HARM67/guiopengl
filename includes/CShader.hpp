#ifndef CSHADER_HPP
# define CSHADER_HPP

# include <iostream>
# include <string>
# include <map>
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# define MAX_SHADER_LENGTH 262144

using namespace std;

class		CShader
{
private:
	GLuint	nbr;
	typedef map <string, CShader *>	t_shader;
	static	t_shader	list;
	CShader() {};
	~CShader() {};
public:
	static	GLuint	create(string program_name, string filename_vs, string filename_fs)
	{
		CShader	*rt = new CShader();
		rt->create_programme_from_files(filename_vs.c_str(), filename_fs.c_str());
		list.insert(pair<string, CShader *>(program_name, rt));
		return (rt->nbr);
	};
	bool create_programme (GLuint vert, GLuint frag);
	bool create_shader (const char* file_name, GLuint* shader, GLenum type);
	bool parse_file_into_str (const char* file_name, char* shader_str, int max_len);

	GLuint create_programme_from_files (string vert_file_name, string frag_file_name);
};
#endif
