/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:41:57 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/31 17:41:57 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "X11_events.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#define HEIGHT WIN_HEIGHT
#define WIDTH WIN_WIDTH
/*
void set_img_background(t_sdl_img *img, uint32_t color)
{
	int i;
	uint32_t *text;

	i = -1;
	text = (uint32_t *)img->array;
	while (++i < img->width * img->height)
		text[i] = color;
}*/

void set_img_background(t_data *img, uint32_t color)
{
	int i;
	uint32_t *text;

	i = -1;
	text = (uint32_t *)img->addr;
	while (++i < img->width * img->height)
		text[i] = color;
}

void    test_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height)
		return ;
	dst = data->addr + (y * data->width + x * data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void    init_data(t_data *data, void *mlx, int w, int h)
{
	data->img = mlx_new_image(mlx, w, h);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
								 &(data->line_length), &(data->endian));
	data->width = w;
	data->height = h;
}

int loop_handler(t_game *game)
{
	uint32_t    rgb[] = {0xFF0000, 0x00FF00, 0x0000FF};

	//printf("IN LOOP, ARG ADRESS : %p\n", game);
	set_img_background(&(game->img), rgb[rand() % 3]);
	 /*   SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = 1;*/
	mlx_put_image_to_window(game->mlx, game->win, (game->img).img, (int)game->x, (int)game->y);
	return (0);
}

int	key_handler(int keycode, t_game *game)
{
	double	increment;

	increment = CLOCKS_PER_SEC / 60;
	printf("Keycode : %d\n", keycode);
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == FORWARD_KEY)
		game->y -= increment;
	if (keycode == BACKWARD_KEY)
		game->y += increment;
	if (keycode == RIGHT_KEY)
		game->x += increment;
	if (keycode == LEFT_KEY)
		game->x -= increment;
	if (keycode == C_KEY)
		mlx_mouse_move(game->mlx, game->win, 0, 0);
	return (0);
}

void	check_screen_size(void *mlx_ptr)
{
	int	x;
	int	y;
	
	mlx_get_screen_size(mlx_ptr, &x, &y);
	printf("SCREEN SIZE : W: %d H: %d\n", x, y);
}

int	mouse_handler(int button, int x, int y, t_game *game)
{
	(void)game;
	printf("MOUSE BUTTON : %d at x: %d, y:%d\n", button, x, y);
	return (0);
}

int	leave(void *arg)
{
	(void)arg;
	printf("EXITING\n");
	exit(0);
	return (0);
}

int	focus_in_handler(void *arg)
{
	(void)arg;
	printf("FOCUS IN\n");
	return (0);
}

int	focus_out_handler(void *arg)
{
	(void)arg;
	printf("FOCUS OUT\n");
	return (0);
}

void	hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_handler, game);
	mlx_hook(game->win, ButtonPress, ButtonPressMask, key_handler, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, leave, NULL);
	mlx_hook(game->win, FocusIn, FocusChangeMask, focus_in_handler, NULL);
	mlx_hook(game->win, FocusOut, FocusChangeMask, focus_out_handler, NULL);
	mlx_mouse_hook(game->win, mouse_handler, game);
	mlx_loop_hook(game->mlx, loop_handler, game);
}

int main(int argc, char **argv)
{
	t_game      game;

	if (argc < 2)
	{
		printf("ERROR : Need a .xpm argument\n");
		exit(1);
	}
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "my win");
	init_data(&(game.img), game.mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game.chibi.img = mlx_xpm_file_to_image(game.mlx, argv[1], &(game.chibi.width), &(game.chibi.height));
	mlx_put_image_to_window(game.mlx, game.win, game.chibi.img, 0, 0);
	hooks(&game);
	check_screen_size(game.mlx);
	mlx_do_key_autorepeaton(game.mlx);
	mlx_loop(game.mlx);

	/* unreachable, like in real mlx */
	mlx_destroy_image(game.mlx, (game.img).img);
	mlx_destroy_window(game.mlx, game.win);
	return (0);
}
