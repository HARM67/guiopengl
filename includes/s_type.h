#ifndef S_TYPE_H
# define S_TYPE_H

typedef struct s_position	t_position;
typedef struct s_size		t_size;
typedef struct s_color		t_color;
typedef struct s_command	t_command;

struct s_command
{
	bool	key_right;
	bool	key_left;
	bool	key_down;
	bool	key_up;
};

struct				s_position
{
	float			x;
	float			y;
};

struct				s_size
{
	float			width;
	float			height;
};

struct				s_color
{
	float			red;
	float			green;
	float			blue;
	float			alpha;
};
#endif
