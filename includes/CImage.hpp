#ifndef CIMAGE_HPP
# define CIMAGE_HPP
# include "CApplication.hpp"

struct	bmp_header
{
	char			signature[2];
	unsigned int	file_size;
	char			reserved[4];
};

class	CImage
{
	public:
		CImage();
		~CImage();
};
#endif
