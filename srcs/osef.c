int main(int argc, char **argv)
{
    int         quit;
   // SDL_Event   event;
    t_game      game;
    uint32_t    rgb[] = {0xFF0000, 0x00FF00, 0x0000FF};
    t_data      (game.img);

    (void)argv;
    (void)argc;
    quit = 0;
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "my win");
    init_data(&(game.img), game.mlx, 600, 400);
    mlx_loop_hook(game.mlx, loop_handler, NULL);
    mlx_loop(game.mlx);
    while (!quit)
    {

        set_img_background(&(game.img), rgb[rand() % 3]);
     /*   SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            quit = 1;*/
        mlx_put_image_to_window(game.mlx, game.win, (game.img).img, 100, 100);
    }
    mlx_destroy_image(game.mlx, (game.img).img);
    mlx_destroy_window(game.mlx, game.win);
    return (0);
}
