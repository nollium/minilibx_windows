#ifndef MLX_INT_H
# define MLX_INT_H

# include "SDL.h"
# include <stdint.h>
# include <stdlib.h>

typedef struct	s_mlx_event
{
	int	event;
	int	mask;
	int	(*handler)(void *);
}				t_mlx_event;

typedef struct	s_sdl_var
{
	void		*events_list;
}				t_sdl_var;

typedef struct	s_mlx_img
{
	uint32_t		*array;
	int				bits_per_pixel;
	int				width;
	int				height;
}					t_mlx_img;

typedef struct		s_sdl_win
{
	SDL_Window		*win_ptr;
	t_mlx_img		*img;
	SDL_Renderer	*renderer;
	SDL_Texture		*text;
	int				width;
	int				height;
}					t_sdl_win;

void	*mlx_init(void);
void	*mlx_new_image(t_sdl_var *mlx_ptr, int width, int height);
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
char	*mlx_get_data_addr(t_mlx_img *img_ptr, int *bits_per_pixel,
							int *size_line, int *endian);
void	my_mlx_pixel_put(t_mlx_img *data, int x, int y, int color);
void	draw_text(t_mlx_img *text, t_mlx_img *img, int x0, int y0);
int		mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, t_mlx_img *img_ptr,
								int x, int y);
int		mlx_destroy_image(t_sdl_var *mlx_ptr, t_mlx_img *img_ptr);
int		mlx_destroy_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr);

#endif