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

int main(int argc, char **argv)
{
    int         quit;
   // SDL_Event   event;
    void        *mlx;
    void        *win;
    uint32_t    rgb[] = {0xFF0000, 0x00FF00, 0x0000FF};
    t_data      data;

    (void)argv;
    (void)argc;
    quit = 0;
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "my win");
    init_data(&data, mlx, 600, 400);
    while (!quit)
    {

        set_img_background(&data, rgb[rand() % 3]);
     /*   SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = 1;*/
        mlx_put_image_to_window(mlx, win, data.img, 100, 100);
    }
    mlx_destroy_image(mlx, data.img);
    mlx_destroy_window(mlx, win);
    //SDL_Quit();
    return (0);
}
