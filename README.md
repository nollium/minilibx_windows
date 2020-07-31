# (WORK IN PROGRESS) SDL2 based minilibx port for windows
This port is based on the X11 based minilibx for linux of 42Paris school [https://github.com/42Paris/minilibx-linux/](https://github.com/42Paris/minilibx-linux/)
I don't currently think that I will completely finish it, my current goal is to make a mlx port behaving in the same way that X11 mlx does with code written for the X11 mlx that only uses basic mlx features like keyboard events (like my mandelbrot viewer [https://github.com/Dirty-No/mandelbrot_viewer](https://github.com/Dirty-No/mandelbrot_viewer))

Events are not currently implemented, as it's implementation is fundamentally based on X11, but like macOS ports, we can't use X11, making it the hardest and most boring part to port.

Fonctions currently implemented  :

    void  *mlx_init(void);
    void  *mlx_new_image(void  *mlx_ptr, int  width, int  height);
    void  *mlx_new_window(void  *mlx_ptr, int  size_x, int  size_y, char  *title);
    char  *mlx_get_data_addr(void  *img_ptr, int  *bits_per_pixel, int  *size_line, int  *endian);
    void  my_mlx_pixel_put(void  *data, int  x, int  y, int  color);
    int  mlx_put_image_to_window(void  *mlx_ptr, void  *win_ptr, void  *img_ptr,int  x, int  y);
    int  mlx_destroy_image(void  *mlx_ptr, void  *img_ptr);
    int  mlx_destroy_window(void  *mlx_ptr, void  *win_ptr);
    int  mlx_loop_hook (void  *mlx_ptr, int (*funct_ptr)(), void  *param);
    int  mlx_loop (void  *mlx_ptr);

