#include "cub3d.h"

static void	player_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[RAYS_IMG].ptr, 0, 0);
	my_destroy_image(mlx, &img[RAYS_IMG]);
	// mlx_put_image_to_window(mlx, win, img[NOSE_IMG].ptr, 0, 0);
	// my_destroy_image(mlx, &img[NOSE_IMG]);
	mlx_put_image_to_window(mlx, win, img[PLAYER_IMG].ptr,
		data()->player.x * GRID_SIZE - PLAYER_SIZE / 2,
		data()->player.y * GRID_SIZE - PLAYER_SIZE / 2);
}

static void	minimap_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[MINIMAP_IMG].ptr, 0, 0);
	player_to_window_buffer(mlx, win, img);
}

static void	micromap_to_window_buffer(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[MICROMAP_IMG].ptr, MICROMAP_OFFSET, MICROMAP_OFFSET);
	mlx_put_image_to_window(mlx, win, img[PLAYER_IMG].ptr,
		MICROMAP_OFFSET + MICROMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2,
		MICROMAP_OFFSET + MICROMAP_RADIUS * GRID_SIZE - PLAYER_SIZE / 2);
	my_destroy_image(mlx, &img[MICROMAP_IMG]);
	img[MICROMAP_IMG].ptr = NULL;
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
	t_img	*img;

	mlx = data()->mlx;
	win = data()->win;
	img = data()->imgs;
	environment_to_window_buffer(mlx, win, img);
	if (MINIMAP)
		minimap_to_window_buffer(mlx, win, img);
	if (MICROMAP)
		micromap_to_window_buffer(mlx, win, img);
	my_destroy_image(mlx, &img[RAYS_IMG]);
	fps_to_window_buffer(); //remove
}

int	game(t_keys *keys)
{
	player_update_position(keys);
	rays_create();
	rays_draw_to_image();
	// player_nose_draw_to_image();
	walls_draw_to_image();
	micromap_draw_to_image();
	window_set_up();
	return (EXIT_SUCCESS);
}
