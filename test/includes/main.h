#ifndef MAIN_H

# include <stdint.h>
# include "X11_events.h"
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_data	chibi;
	double	x;
	double	y;
}				t_game;


# ifdef _WIN32

#  define FORWARD_KEY           122
#  define BACKWARD_KEY          115
#  define LEFT_KEY                      113
#  define RIGHT_KEY                     100
#  define CTRL_KEY                      1073742048
#  define ALT_KEY                       1073742050
#  define C_KEY                         99
#  define ESC_KEY           27

# endif

#endif // MAIN_H
