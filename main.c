#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "main.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#define HEIGHT WIN_HEIGHT
#define WIDTH WIN_WIDTH

void set_img_background(t_sdl_img *img, uint32_t color)
{
    int i;
    uint32_t *text;

    i = -1;
    text = img->array;
    while (++i < img->width * img->height)
        text[i] = color;
}

void    *mlx_init()
{
    t_sdl_var   *mlx;

    mlx = calloc(1, sizeof(t_sdl_var));
    SDL_Init(SDL_INIT_EVERYTHING);
    return (mlx);
}

t_sdl_img    *mlx_new_image(t_sdl_var *mlx_ptr, int width, int height)
{
    t_sdl_img   *img;

    img = calloc(1, sizeof(t_sdl_img));
    img->array = calloc(width * height, sizeof(uint32_t));
    img->bits_per_pixel = sizeof(uint32_t);
    img->height = height;
    img->width = width;
    return (img);
}

void    *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
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
    return (win);
}

char	*mlx_get_data_addr(t_sdl_img *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian)
{
    *bits_per_pixel = img_ptr->bits_per_pixel;
    *size_line = img_ptr->width;
    *endian = 0;
    return ((char *)img_ptr->array);
}

void    my_mlx_pixel_put(t_sdl_img *data, int x, int y, int color)
{
    char    *dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height)
		return ;
	dst = data->array + (y * data->width + x * data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void		draw_text(t_sdl_img *text, t_sdl_img *img, int x0, int y0)
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

int     mlx_put_image_to_window(t_sdl_var *mlx_ptr, t_sdl_win *win_ptr, t_sdl_img *img_ptr,
                                int x, int y)
{
    draw_text(img_ptr, win_ptr->img, x, y);
    SDL_UpdateTexture(win_ptr->text, NULL, win_ptr->img->array, win_ptr->width * sizeof(uint32_t));
    SDL_RenderClear(win_ptr->renderer);
    SDL_RenderCopy(win_ptr->renderer, win_ptr->text, NULL, NULL);
    SDL_RenderPresent(win_ptr->renderer);
    return (1);
}

int main(int argc, char *argv[])
{

    int         quit;
    SDL_Event   event;
    t_sdl_var   *mlx;
    t_sdl_win   *win;
    t_sdl_img   *img;
    uint32_t    rgb[] = {0xFF0000, 0x00FF00, 0x0000FF};

    quit = 0;
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "my win");
    img = mlx_new_image(mlx, 600, 400);
    while (!quit)
    {

        set_img_background(img, rgb[rand() % 3]);
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = 1;
        mlx_put_image_to_window(mlx, win, img, 100, 100);
    }

    SDL_DestroyWindow(win->win_ptr);
    SDL_Quit();
    return (0);
}
