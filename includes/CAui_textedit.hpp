#ifndef CAUI_TEXTEDIT_HPP
# define CAUI_TEXTEDIT_HPP
# include "CAui.hpp"
# include "CAui_texte.hpp"
# include <iostream>
# include "s_type.h"
# include "CFont.hpp"
# include "CAui_cmd.hpp"
# include "CImage.hpp"
# include "CTexture.hpp"

typedef struct Init_textedit t_Init_textedit;

class	CAui_textedit : public CAui_texte
{
private:
	int		selected_character[2];
	static t_Init_textedit	not_use;
	CAui_textedit();
	~CAui_textedit();
public:
	static CAui	*create_textedit()
	{
		return (new CAui_textedit);
	};

	virtual t_size		print_string(t_position vpos);
	virtual t_size		draw(float x, float y);
	virtual void		mouse_button_callback(int button, int action, int mods);
	virtual void		cursor_position_callback(int status, double xpos, double ypos);
	virtual CAui		*why(float x, float y);
	virtual void 		key_callback(unsigned char *b_key, double *key);
};

struct	Init_textedit
{
	Init_textedit()
	{
		CAui::objects.insert(pair<string, CAui *(*)()>("textedit", &CAui_textedit::create_textedit));
	}
};
#endif

