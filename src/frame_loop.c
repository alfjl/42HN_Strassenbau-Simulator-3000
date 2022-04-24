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

static void	sprites_to_window_buffer(void *mlx, void *win)
{
	int nbr;
	int			i;
	static int	counter = 0;

	(void)win;
	(void)mlx;
	nbr = 0;
	while (nbr < SPRITENBR)
	{
		i =  counter / 15 % data()->sprites[nbr].count;
		// mlx_put_image_to_window(mlx, win, imgs[BACKGROUND_IMG].ptr, 0, 0);
		// mlx_put_image_to_window(mlx, win, imgs[WALLS_IMG].ptr, 0, 0);
		// my_destroy_image(mlx, &imgs[WALLS_IMG]);
		// mlx_put_image_to_window(mlx, win, data()->sprites[nbr].sequence[i].ptr, 0, 0);
		// image_fill(&data()->imgs[WALLS_IMG], BLACK);
		image_overlay(&data()->sprites[nbr].sequence[i], &data()->imgs[WALLS_IMG], 200, 200);
		nbr++;
		counter++;
	}
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	if (HAS_ALPHA)
		mlx_put_image_to_window(mlx, win, imgs[BACKGROUND_IMG].ptr, 0, 0);
	if (SPRITES)
		sprites_to_window_buffer(mlx, win);
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
	// if (SPRITES)
	// 	sprites_to_window_buffer(mlx, win);
	if (MINIMAP)
		minimap_to_window_buffer(mlx, win, imgs);
	fps_to_window_buffer(); //remove
}

int	frame_loop(t_controls *controls)
{
	player_update_position(controls);
	controls->mouse_left = false;
	controls->mouse_right = false;
	rays_create();
	walls_draw_to_image();
	if (MINIMAP)
		minimap_draw_to_image();
	window_set_up();
	// int w;
	// int h;
	// mlx_put_image_to_window(data()->mlx, data()->win,
	// 	mlx_xpm_file_to_image(data()->mlx, "./sprites/shovel0.xpm",
	// 		&w, &h), 0, 0);
	// mlx_put_image_to_window(data()->mlx, data()->win,
	// 	mlx_png_file_to_image(data()->mlx, "./textures/dirt2048x2048.png",
	// 		&w, &h), 0, 0);
	return (EXIT_SUCCESS);
}
