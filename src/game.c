# include "cub3d.h"

static void	player_render(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[RAYS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[RAYS_IMG].ptr);
	mlx_put_image_to_window(mlx, win, img[NOSE_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[NOSE_IMG].ptr);
	mlx_put_image_to_window(mlx, win, img[PLAYER_IMG].ptr, data()->player.x * GRID_SIZE - PLAYER_SIZE / 2, data()->player.y * GRID_SIZE - PLAYER_SIZE / 2);
}

static void	minimap_render(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[MINIMAP_IMG].ptr, 0, 0);
	player_render(mlx, win, img);
}

static void	world_render(void *mlx, void *win, t_img *img)
{
	mlx_put_image_to_window(mlx, win, img[BACKGROUND_IMG].ptr, 0, 0);
	mlx_put_image_to_window(mlx, win, img[WALLS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[WALLS_IMG].ptr);
}

static void	window_render()
{
	void	*mlx;
	void	*win;
	t_img	*img;

	mlx = data()->mlx;
	win = data()->win;
	img = data()->imgs;
	world_render(mlx, win, img);
	minimap_render(mlx, win, img);
	fps();
}

int	game(t_keys *keys)
{
	player_update_position(keys);
	minimap();
	walls();
	window_render();
	return (EXIT_SUCCESS);
}
