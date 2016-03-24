#include "CShader.hpp"
CShader::t_shader CShader::list;

bool CShader::parse_file_into_str (const char* file_name, char* shader_str, int max_len)
{
	shader_str[0] = '\0';
	FILE* file = fopen (file_name , "r");
	int current_len = 0;
	char line[2048];
	strcpy (line, "");
	while (!feof (file)) {
		if (NULL != fgets (line, 2048, file)) {
			current_len += strlen (line); // +1 for \n at end
			if (current_len >= max_len)
				cout << "ERROR: shader length is longer than string buffer length " << max_len << endl;
			strcat (shader_str, line);
		}
	}
	if (EOF == fclose (file)) { // probably unnecesssary validation
		cout << "ERROR: closing file from reading" << file_name << endl;
		return false;
	}
	return true;
}

bool CShader::create_shader (const char* file_name, GLuint* shader, GLenum type) {
	char shader_string[MAX_SHADER_LENGTH];
	parse_file_into_str (file_name, shader_string, MAX_SHADER_LENGTH);
	*shader = glCreateShader (type);
	const GLchar* p = (const GLchar*)shader_string;
	glShaderSource (*shader, 1, &p, NULL);
	glCompileShader (*shader);
	return true;
}

bool CShader::create_programme (GLuint vert, GLuint frag)
{
	nbr = glCreateProgram ();
	glAttachShader (nbr, vert);
	glAttachShader (nbr, frag);
	glLinkProgram (nbr);
	GLint params = -1;
	glGetProgramiv (nbr, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		cout << "ERROR: could not link shader programme GL index \n" << nbr << endl;
		return false;
	}
	glDeleteShader (vert);
	glDeleteShader (frag);
	return true;
}

GLuint CShader::create_programme_from_files (string vert_file_name, string frag_file_name)
{
	GLuint vert, frag;
	create_shader (vert_file_name.c_str(), &vert, GL_VERTEX_SHADER);
	create_shader (frag_file_name.c_str(), &frag, GL_FRAGMENT_SHADER);
	create_programme (vert, frag);
	return nbr;
}

