

# (WORK IN PROGRESS) SDL2 based minilibx port for Windows
This port is based on the X11 based minilibx for linux of 42Paris school [https://github.com/42Paris/minilibx-linux/](https://github.com/42Paris/minilibx-linux/)

## THIS NOT AN OFFICIAL PORT, USE AT YOUR OWN RISK
The Minilibx was originally created by Olivier Crouzet (ol@42), this only a port of his (and other contributors) work for Windows using the Simple DirectMedia Layer 2 library.

The SDL2 is available for [  Microsoft Windows](https://fr.wikipedia.org/wiki/Microsoft_Windows "Microsoft Windows"),  [GNU/Linux](https://fr.wikipedia.org/wiki/GNU/Linux "GNU/Linux"),  [Android](https://fr.wikipedia.org/wiki/Android "Android"),  [macOS](https://fr.wikipedia.org/wiki/MacOS "MacOS"),  [iOS](https://fr.wikipedia.org/wiki/IOS "IOS"),  [FreeBSD](https://fr.wikipedia.org/wiki/FreeBSD "FreeBSD")  and [Haiku](https://fr.wikipedia.org/wiki/Haiku_(syst%C3%A8me_d%27exploitation) "Haiku (système d'exploitation)") so this port should probably be adaptable for all those OS without too much effort. 
However, I've only tested this for Windows.

My goal when I first started this port was to make a mlx port behaving in the same way that X11 mlx does with code written for the X11 mlx that only uses basic mlx features like keyboard events (like my mandelbrot viewer [https://github.com/Dirty-No/mandelbrot_viewer](https://github.com/Dirty-No/mandelbrot_viewer))

This is now done. My next goal is to implement the features required by my cub3D, which basically are almost all of X11 mlx features + the mlx_mouse_get_pos() function (because it's somehow not implemented for linux even if it's only 1 line of code)

Only keyboard events are currently implemented.

Fonctions currently implemented  :

    void    	*mlx_init(void);
    void    	*mlx_new_image(void *mlx_ptr, int width, int height);
    char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
    			                int *size_line, int *endian);
    int		mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
                                    int x, int y);
    int		mlx_destroy_image(void *mlx_ptr, void *img_ptr);
	                                        			                
    void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
    int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
    
    int		mlx_key_hook (void  *win_ptr, int (*funct_ptr)(), void  *param);
    int	    	mlx_hook(void *win_ptr, int x_event, int x_mask,
                     	int (*funct)(), void *param);
    int	    	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
    int	    	mlx_loop (void *mlx_ptr);
    
    void    	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);

If you are interested in this port but need more features from the original mlx, please make an issue, if you do so hopefully I should be able to implement them pretty quickly.

## INSTALLATION
You will need Mingw (Minimalist GNU for Windows) tools : 
[http://www.mingw.org/wiki/Install_MinGW](http://www.mingw.org/wiki/Install_MinGW)
(which ports GNU GCC and GNU Make to Windows)

Make in the project's root directory will compile the lib and a test executable.

You will need to place SDL2.dll, SDL2_image.dll next to your executable. (because i still don't understand how to change the path to dynamic libs yes i am noob dev please help me)

You'll need to compile with the following links :
 `-L"$(MLX_DIRECTORY)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lmingw32 -lSDL2main -luser32 -lgdi32 -lwinmm -ldxguid`


## EPILEPSY WARNING

The default test displays a rectangle changing colors at every frame which can probably cause you a stroke or something if you are epileptic.

Feel free to contribute to the project by making issues, pull request, or by contacting me directly, any improvements or ideas are much welcome.
