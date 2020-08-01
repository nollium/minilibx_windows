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

/*
** Apparently key repeat has to be handled manually with SDL2, so this is not implemented yet
*/

/*
int	mlx_do_key_autorepeatoff(void *mlx_ptr);
{
	(void)mlx_ptr;
	SDL_EnableKey
	return (1);
}

int	mlx_do_key_autorepeaton(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (1);
}*/


static void	init_X11_events_map(uint32_t *map)
{
	map[SDL_KEYDOWN] = KeyPress;
	map[SDL_KEYUP] = KeyRelease;

	map[SDL_MOUSEBUTTONDOWN] = ButtonPress;
	map[SDL_MOUSEBUTTONUP] = ButtonRelease;
}

void    *mlx_init()
{
	t_sdl_var   *mlx;

	mlx = calloc(1, sizeof(t_sdl_var));
	SDL_Init(SDL_INIT_EVERYTHING);
	init_X11_events_map(mlx->X11_event_map);
	return (mlx);
}

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
	ft_lstadd_front(&(mlx_ptr->win_list), ft_lstnew(win));
	win->mlx_ptr = mlx_ptr;
	return (win);
}

char	*mlx_get_data_addr(SDL_Surface *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian)
{
	*bits_per_pixel = img_ptr->format->BitsPerPixel;
	*size_line = img_ptr->pitch;
	*endian = 0;
	return ((char *)(img_ptr->pixels));
}

/* should not be used
void    my_mlx_pixel_put(SDL_Surface *data, int x, int y, int color)
{
	char    *dst;

	if (x <= 0 || x >= data->w || y <= 0 || y >= data->h)
		return ;
	dst = ((char *)data->pixels) + (y * data->w + x * (data->format->BitsPerPixel) / 8);
	*(unsigned int *)dst = color;
}*/

int     mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, SDL_Surface *img_ptr,
								int x, int y)
{
	SDL_Rect rect;

	(void)mlx_ptr;
	rect = (SDL_Rect){.w = img_ptr->w, .h = img_ptr->h, .x = x, .y = y};
	SDL_UpdateTexture(win_ptr->text, &rect, img_ptr->pixels,
					img_ptr->pitch);
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

SDL_Surface	*mlx_xpm_file_to_image(t_sdl_var *mlx_ptr, char *filename,
			       int *width, int *height)
{
	SDL_RWops		*rwop;
	SDL_Surface		*src;
	SDL_Surface		*img;
	SDL_PixelFormat fmt;

	if(!(rwop = SDL_RWFromFile(filename, "rb")))
		return (NULL);
	src = IMG_LoadXPM_RW(rwop);
	fmt = (SDL_PixelFormat)
	{
		.BitsPerPixel = BITS_PER_PIXELS,
		.BytesPerPixel = BITS_PER_PIXELS / 8
	};
	img = SDL_ConvertSurface(src, &fmt, 0);
	SDL_FreeRW(rwop);
	SDL_FreeSurface(src);
	*width = img->w;
	*height = img->h;
	return (img);
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

int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param)
{
	return (mlx_hook(win_ptr, KeyPress, KeyPressMask, funct_ptr, param));
}

int	mlx_loop (t_sdl_var *mlx_ptr)
{
	SDL_Event	sdl_event;
	t_mlx_event	*mlx_event;
	int			(*hook)();

	while (42)
	{
		while (SDL_PollEvent(&sdl_event))
		{
			mlx_event = mlx_ptr->hooks + mlx_ptr->X11_event_map[sdl_event.type];
			hook = mlx_event->hook;
			if (hook)
			{
				if (SDL_MOUSEBUTTONDOWN <= sdl_event.type && sdl_event.type <= SDL_MOUSEBUTTONUP)
					hook(sdl_event.button.button, mlx_event->param);
				else if (SDL_KEYDOWN <= sdl_event.type && sdl_event.type <= SDL_KEYUP)
					hook((int)sdl_event.key.keysym.sym, mlx_event->param);
				else
					hook(mlx_event->param);
			}
		}
		mlx_ptr->loop_hook(mlx_ptr->loop_param);
	}	
}
