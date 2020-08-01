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

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "mlx.h"


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

	printf("IN LOOP, ARG ADRESS : %p\n", game);
	set_img_background(&(game->img), rgb[rand() % 3]);
	 /*   SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = 1;*/
	mlx_put_image_to_window(game->mlx, game->win, (game->img).img, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}
#include "SDL.h"
int main(int argc, char **argv)
{
	int         quit;
   // SDL_Event   event;
	t_game      game;
	SDL_Surface text;

	(void)argv;
	(void)argc;
	quit = 0;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "my win");
	init_data(&(game.img), game.mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop_hook(game.mlx, loop_handler, &game);
	mlx_loop(game.mlx);
	mlx_destroy_image(game.mlx, (game.img).img);
	mlx_destroy_window(game.mlx, game.win);
	return (0);
}
