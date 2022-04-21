#include "cub3d.h"

static void	minimap_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	mlx_put_image_to_window(mlx, win, imgs[MINIMAP_IMG].ptr, MINIMAP_OFFSET,
		MINIMAP_OFFSET);
	mlx_put_image_to_window(mlx, win, imgs[PLAYER_IMG].ptr,
		MINIMAP_OFFSET + MINIMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2,
		MINIMAP_OFFSET + MINIMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2);
	my_destroy_image(mlx, &imgs[MINIMAP_IMG]);
	imgs[MINIMAP_IMG].ptr = NULL;
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	if (HAS_ALPHA)
		mlx_put_image_to_window(mlx, win, imgs[BACKGROUND_IMG].ptr, 0, 0);
	mlx_put_image_to_window(mlx, win, imgs[WALLS_IMG].ptr, 0, 0);
	my_destroy_image(mlx, &imgs[WALLS_IMG]);
}

static void	window_set_up(void)
{
	void	*mlx;
	void	*win;
	t_img	*imgs;

	mlx = data()->mlx;
	win = data()->win;
	imgs = data()->imgs;
	environment_to_window_buffer(mlx, win, imgs);
	if (MINIMAP)
		minimap_to_window_buffer(mlx, win, imgs);
	fps_to_window_buffer(); //remove
}

int	frame_loop(t_keys *keys)
{
	player_update_position(keys);
	rays_create();
	walls_draw_to_image();
	if (MINIMAP)
		minimap_draw_to_image();
	window_set_up();
	// int w;
	// int h;
	// mlx_put_image_to_window(data()->mlx, data()->win, mlx_png_file_to_image(data()->mlx, "./textures/dirt2048x2048.png", &w, &h), 0, 0);
	return (EXIT_SUCCESS);
}
