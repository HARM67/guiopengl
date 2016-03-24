#ifndef CAUI_HPP
# define CAUI_HPP
# include <iostream>
# include <vector>
# include "s_type.h"

using namespace std;

class	CAui
{
protected:
	bool		visible;
	t_position	pos;
	t_size		size;
	vector <CAui*>	content;
	
public:
	CAui();
	~CAui();
	virtual void	draw();
	virtual void	draw(float, float){};
	static CAui	*create_instant()
	{
		return (new CAui);
	};
	void	set_position(float x, float y);
	void	set_size(float width, float height);
	void	add_Elem(CAui *elem);
};
#endif
