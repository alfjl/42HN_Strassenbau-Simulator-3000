#include "cub3d.h"

static void	player_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[RAYS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[RAYS_IMG].ptr);
	mlx_put_image_to_window(mlx, win, img[NOSE_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[NOSE_IMG].ptr);
	mlx_put_image_to_window(mlx, win, img[PLAYER_IMG].ptr,
		data()->player.x * GRID_SIZE - PLAYER_SIZE / 2,
		data()->player.y * GRID_SIZE - PLAYER_SIZE / 2);
}

static void	minimap_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[MINIMAP_IMG].ptr, 0, 0);
	player_to_window_buffer(mlx, win, img);
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[BACKGROUND_IMG].ptr, 0, 0);
	mlx_put_image_to_window(mlx, win, img[WALLS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[WALLS_IMG].ptr);
}

static void	window_set_up(void)
{
	void	*mlx;
	void	*win;
	t_img	*img;

	mlx = data()->mlx;
	win = data()->win;
	img = data()->imgs;
	environment_to_window_buffer(mlx, win, img);
	if (MINIMAP)
		minimap_to_window_buffer(mlx, win, img);
	fps_to_window_buffer();
}

int	game(t_keys *keys)
{
	player_update_position(keys);
	rays_create();
	rays_draw_to_image();
	player_nose_draw_to_image();
	walls_draw_to_image();
	window_set_up();
	return (EXIT_SUCCESS);
}
