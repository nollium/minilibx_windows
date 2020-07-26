#ifndef MAIN_H

#include <SDL2/SDL.h>

typedef struct  s_sdl_var
{
    void      *events_list;
}               t_sdl_var;

typedef struct  s_sdl_img
{
    uint32_t        *array;
    int             bits_per_pixel;
    int             width;
    int             height;
}               t_sdl_img;

typedef struct  s_sdl_win
{
    SDL_Window      *win_ptr;
    t_sdl_img       *img;
    SDL_Renderer    *renderer;
    SDL_Texture     *text;
    int             width;
    int             height;
}               t_sdl_win;

typedef struct s_data
{
    char    *addr;
    int     line_length;
    int     bits_per_pixel;
}             t_data;

#endif // MAIN_H
