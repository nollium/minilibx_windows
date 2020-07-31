#ifndef MLX_H
# define MLX_H

void    *mlx_init(void);
void    *mlx_new_image(void *mlx_ptr, int width, int height);
void    *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
			                int *size_line, int *endian);
void    my_mlx_pixel_put(void *data, int x, int y, int color);
void	draw_text(void *text, void *img, int x0, int y0);
int     mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
                                int x, int y);
int		mlx_destroy_image(void *mlx_ptr, void *img_ptr);
int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
#endif