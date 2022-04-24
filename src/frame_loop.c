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

static void	static_sprites_to_window_buffer(void)
{
	int 		nbr;
	int			i;
	int			*counter;
	int			*sign;
	int			max;

	nbr = 0;
	while (nbr < SPRITENBR)
	{
		counter = &data()->sprites[nbr].counter;
		sign = &data()->sprites[nbr].sign;
		max = data()->sprites[nbr].count;
		i = *counter / 10 % max;
		if (data()->sprites[nbr].enabled)
			image_overlay(&data()->sprites[nbr].sequence[i], &data()->imgs[WALLS_IMG], 200, 200 + i * 5);
		*counter += *sign;
		if (*counter == 0 || *counter == (max - 1) * SPRITE_SPEED)
			*sign *= -1;
		nbr++;
	}
}

static void	environment_to_window_buffer(void *mlx, void *win, t_img *imgs)
{
	if (HAS_ALPHA)
		mlx_put_image_to_window(mlx, win, imgs[BACKGROUND_IMG].ptr, 0, 0);
	if (SPRITES)
		static_sprites_to_window_buffer();
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
	// 	static_sprites_to_window_buffer();
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
