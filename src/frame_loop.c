#include "cub3d.h"

static void	micromap_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	mlx_put_image_to_window(mlx, win, imgs[MICROMAP_IMG].ptr, MICROMAP_OFFSET,
		MICROMAP_OFFSET);
	mlx_put_image_to_window(mlx, win, imgs[PLAYER_IMG].ptr,
		MICROMAP_OFFSET + MICROMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2,
		MICROMAP_OFFSET + MICROMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2);
	my_destroy_image(mlx, &imgs[MICROMAP_IMG]);
	imgs[MICROMAP_IMG].ptr = NULL;
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
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
	if (MICROMAP)
		micromap_to_window_buffer(mlx, win, imgs);
	fps_to_window_buffer(); //remove
}

int	frame_loop(t_keys *keys)
{
	player_update_position(keys);
	rays_create();
	walls_draw_to_image();
	if (MICROMAP)
		micromap_draw_to_image();
	window_set_up();
	return (EXIT_SUCCESS);
}
