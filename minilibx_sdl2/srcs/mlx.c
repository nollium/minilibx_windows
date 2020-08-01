/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:45:21 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 17:45:21 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

void    *mlx_init()
{
	t_sdl_var   *mlx;

	mlx = calloc(1, sizeof(t_sdl_var));
	SDL_Init(SDL_INIT_EVERYTHING);
	return (mlx);
}

/*
** I should implement that with SDL_Surface instead.. 
*/

void    *mlx_new_image(t_sdl_var *mlx_ptr, int width, int height)
{
	(void)mlx_ptr;
	return (SDL_CreateRGBSurface(0, width, height, BITS_PER_PIXELS, 0, 0, 0, 0));
}

void    *mlx_new_window(t_sdl_var *mlx_ptr, int size_x, int size_y, char *title)
{
	t_sdl_win   *win;

	win = calloc(1, sizeof(t_sdl_win));
	win->win_ptr = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  size_x, size_y, 0);
	win->renderer = SDL_CreateRenderer(win->win_ptr,
									   1, SDL_RENDERER_ACCELERATED);
	win->width = size_x;
	win->height = size_y;
	win->text = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888,
							 SDL_TEXTUREACCESS_STATIC,
							 win->width, win->height);
	//win->img = mlx_new_image(mlx_ptr, size_x, size_y);
	ft_lstadd_front(&(mlx_ptr->win_list), ft_lstnew(win));
	win->mlx_ptr = mlx_ptr;
	return (win);
}

char	*mlx_get_data_addr(SDL_Surface *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian)
{
	*bits_per_pixel = img_ptr->format->BitsPerPixel;
	*size_line = img_ptr->w;
	*endian = 0;
	return ((char *)(img_ptr->pixels));
}

void    my_mlx_pixel_put(SDL_Surface *data, int x, int y, int color)
{
	char    *dst;

	if (x <= 0 || x >= data->w || y <= 0 || y >= data->h)
		return ;
	dst = ((char *)data->pixels) + (y * data->w + x * (data->format->BitsPerPixel) / 8);
	*(unsigned int *)dst = color;
}

/*
** should be unused 
*/

/*
void		draw_text(SDL_Surface *text, SDL_Surface *img, int x0, int y0)
{
	int	x;
	int	y;

	x = -1;
	while (++x < text->w)
	{
		y = -1;
		while (++y < text->h)
			my_mlx_pixel_put(img, x + x0, y + y0,
							((char *)text->pixels)[text->w * y + x * img->format->BitsPerPixel]);
	}
}*/

int     mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, SDL_Surface *img_ptr,
								int x, int y)
{
	SDL_Rect rect;

	(void)mlx_ptr;
	rect = (SDL_Rect){.w = img_ptr->w, .h = img_ptr->h, .x = x, .y = y};
	//draw_text(img_ptr, win_ptr->img, x, y);
	//SDL_CreateTextureFromSurface()
	SDL_UpdateTexture(win_ptr->text, &rect, img_ptr->pixels,
					img_ptr->w * img_ptr->format->BytesPerPixel);
	SDL_RenderClear(win_ptr->renderer);
	SDL_RenderCopy(win_ptr->renderer, win_ptr->text, NULL, NULL);
	SDL_RenderPresent(win_ptr->renderer);
	return (1);
}

int	mlx_destroy_image(t_sdl_var *mlx_ptr, SDL_Surface *img_ptr)
{
	(void)mlx_ptr;
	SDL_FreeSurface(img_ptr);
	return (1);
}

int	mlx_destroy_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr)
{
	SDL_DestroyWindow(win_ptr->win_ptr);
	SDL_DestroyRenderer(win_ptr->renderer);
	SDL_DestroyTexture(win_ptr->text);
	ft_lstdelone(ft_lstchr(mlx_ptr->win_list, win_ptr), NULL);
	return (1);
}

int	mlx_hook(t_sdl_win *win_ptr, int x_event, int x_mask,
                 int (*funct)(), void *param)
{
	t_sdl_var 	*mlx;

	mlx = win_ptr->mlx_ptr;
	mlx->hooks[x_event].hook = funct;
	mlx->hooks[x_event].param = param;
	mlx->hooks[x_event].mask = x_mask;
	return (1);
}

int	mlx_loop_hook (t_sdl_var *mlx_ptr, int (*funct_ptr)(), void *param)
{
	mlx_ptr->loop_hook = funct_ptr;
	mlx_ptr->loop_param = param;
	return (1);
}

int	mlx_loop (t_sdl_var *mlx_ptr)
{
	SDL_Event event;

	while (42)
	{
		mlx_ptr->loop_hook(mlx_ptr->loop_param);
	}	
}
