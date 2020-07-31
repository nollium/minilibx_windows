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

void    *mlx_new_image(t_sdl_var *mlx_ptr, int width, int height)
{
	t_mlx_img   *img;

	(void)mlx_ptr;
	img = calloc(1, sizeof(t_mlx_img));
	img->array = calloc(width * height, sizeof(uint32_t));
	img->bits_per_pixel = sizeof(uint32_t);
	img->height = height;
	img->width = width;
	return (img);
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
	win->img = mlx_new_image(mlx_ptr, size_x, size_y);
	ft_lstadd_front(&(mlx_ptr->win_list));
	win->mlx_ptr = mlx_ptr;
	return (win);
}

char	*mlx_get_data_addr(t_mlx_img *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian)
{
	*bits_per_pixel = img_ptr->bits_per_pixel;
	*size_line = img_ptr->width;
	*endian = 0;
	return ((char *)img_ptr->array);
}

void    my_mlx_pixel_put(t_mlx_img *data, int x, int y, int color)
{
	uint32_t    *dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height)
		return ;
	dst = data->array + (y * data->width + x * data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void		draw_text(t_mlx_img *text, t_mlx_img *img, int x0, int y0)
{
	int	x;
	int	y;

	x = -1;
	while (++x < text->width)
	{
		y = -1;
		while (++y < text->height)
			my_mlx_pixel_put(img, x + x0, y + y0,
							text->array[text->width * y + x]);
	}
}

int     mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, t_mlx_img *img_ptr,
								int x, int y)
{
	(void)mlx_ptr;
	draw_text(img_ptr, win_ptr->img, x, y);
	SDL_UpdateTexture(win_ptr->text, NULL, win_ptr->img->array, win_ptr->width * sizeof(uint32_t));
	SDL_RenderClear(win_ptr->renderer);
	SDL_RenderCopy(win_ptr->renderer, win_ptr->text, NULL, NULL);
	SDL_RenderPresent(win_ptr->renderer);
	return (1);
}

int	mlx_destroy_image(t_sdl_var *mlx_ptr, t_mlx_img *img_ptr)
{
	(void)mlx_ptr;
	free(img_ptr->array);
	free(img_ptr);
	return (1);
}

int	mlx_destroy_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr)
{
	SDL_DestroyWindow(win_ptr->win_ptr);
	SDL_DestroyRenderer(win_ptr->renderer);
	SDL_DestroyTexture(win_ptr->text);
	mlx_destroy_image(mlx_ptr, win_ptr->img);
	ft_lstdelone(ft_lstchr(mlx_ptr->win_list, win_ptr), NULL);
	return (1);
}

int	mlx_hook(t_sdl_win *win_ptr, int x_event, int x_mask,
                 int (*funct)(), void *param);
{
	t_sdl_var 	*mlx;

	mlx = win_ptr->mlx_ptr;
	mlx->hooks[x_event].hook = funct;
	mlx->hooks[x_event].param = param;
	mlx->hooks[x_event].mask = x_mask;
	return (1);
}

int	mlx_loop (t_sdl_var *mlx_ptr)
{
	
}
