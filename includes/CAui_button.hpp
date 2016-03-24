#ifndef CAUI_BUTTON_HPP
# define CAUI_BUTTON_HPP
#include "CAui.hpp"

class	CAui_button : public CAui
{
public:
	CAui_button(){cout << "Je suis un bouton" << endl;};
	~CAui_button(){};
	static CAui	*create_button() {return (new CAui_button);};
};
#endif
