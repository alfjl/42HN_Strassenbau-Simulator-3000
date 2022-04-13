# include "cub3d.h"

static void	window_render()
{
	void	*mlx;
	void	*win;
	t_img	*img;

	mlx = data()->mlx;
	win = data()->win;
	img = data()->imgs;
	mlx_put_image_to_window(mlx, win, img[BACKGROUND_IMG].ptr, 0, 0);
	walls();
	mlx_put_image_to_window(mlx, win, img[WALLS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[WALLS_IMG].ptr);
	mlx_put_image_to_window(mlx, win, img[MINIMAP_IMG].ptr, 0, 0);
	minimap();
	mlx_put_image_to_window(mlx, win, img[RAYS_IMG].ptr, 0, 0);
	mlx_destroy_image(mlx, img[RAYS_IMG].ptr);
	fps();
}

int	game(t_keys *keys)
{
	player_update_position(keys);
	window_render();
	return (EXIT_SUCCESS);
}
