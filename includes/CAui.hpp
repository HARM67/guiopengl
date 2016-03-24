#ifndef CAUI_HPP
# define CAUI_HPP
//# include "CApplication.hpp"
//# include "CAui_container.hpp"
# include <iostream>
# include <vector>

using namespace std;


class	CAui
{
	bool		visible;
	
	public:
		vector <CAui*>	content;
		CAui();
		~CAui();
	static CAui	*create_instant() {return (new CAui);};
};
#endif
