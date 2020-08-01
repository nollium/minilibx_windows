#ifndef MAIN_H

#include <stdint.h>

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
}				t_game;


#endif // MAIN_H
