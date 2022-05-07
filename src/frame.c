#include "cub3d.h"

static void	static_frame_minimap_to_window_buffer(void *mlx,
	void *win, t_img *imgs)
{
	int	origin;

	origin = MINIMAP_OFFSET + MINIMAP_RADIUS * MAP_GRID_SIZE
		- MINIMAP_PLAYER_SIZE / 2;
	mlx_put_image_to_window(mlx, win, imgs[MINIMAP_IMG].ptr, MINIMAP_OFFSET,
		MINIMAP_OFFSET);
	mlx_put_image_to_window(mlx, win, imgs[PLAYER_IMG].ptr, origin, origin);
}

// static void	static_sprites_to_window_buffer(void)
// {
// 	int 		nbr;
// 	int			i;
// 	int			*counter;
// 	int			*sign;
// 	int			max;

// 	nbr = 0;
// 	while (nbr < SPRITE_NBR)
// 	{
// 		counter = &data()->sprites[nbr].counter;
// 		sign = &data()->sprites[nbr].sign;
// 		max = data()->sprites[nbr].count;
// 		i = *counter / 10 % max;
// 		if (data()->sprites[nbr].enabled)
// 			image_overlay(&data()->sprites[nbr].sequence[i],
// 				&data()->imgs[ENV_IMG], 200, 200 + i * 5);
// 		*counter += *sign;
// 		if (*counter == 0 || *counter == (max - 1) * data()->sprites[nbr].speed)
// 			*sign *= -1;
// 		nbr++;
// 	}
// }

static void	static_frame_player_sprite_to_window_buffer(void)
{
	int			nbr;
	int			i;
	int			*counter;
	int			*sign;
	int			max;

	nbr = data()->player.status;
	counter = &data()->sprites[nbr].counter;
	sign = &data()->sprites[nbr].sign;
	max = data()->sprites[nbr].count;
	i = *counter / 10 % max;
	image_overlay(&data()->sprites[nbr].sequence[i], &data()->imgs[ENV_IMG],
		200, 200 + i * 5);
	*counter += *sign;
	if (*counter == 0 || *counter == (max - 1) * data()->sprites[nbr].speed)
	{
		if (nbr == HITTING)
		{
			*counter = 0;
			data()->player.status = IDLE;
		}
		else
			*sign *= -1;
	}
}

static void	static_frame_environment_to_window_buffer(void *mlx, void *win,
	t_img *imgs)
{
	if (SPRITES_ENABLED)
		static_frame_player_sprite_to_window_buffer();
	mlx_put_image_to_window(mlx, win, imgs[ENV_IMG].ptr, 0, 0);
	// my_destroy_image(mlx, &imgs[ENV_IMG]);
}

static void	frame_set_up_window(void)
{
	void	*mlx;
	void	*win;
	t_img	*imgs;

	mlx = data()->mlx;
	win = data()->win;
	imgs = data()->imgs;
	static_frame_environment_to_window_buffer(mlx, win, imgs);
	if (MINIMAP_ENABLED)
		static_frame_minimap_to_window_buffer(mlx, win, imgs);
	if (FPS_ENABLED)
		fps_to_window_buffer(); //remove
	// if (SKY_ENABLED)
	// 	mlx_put_image_to_window(mlx, win, imgs[SKY_IMG].ptr, 0, 0);
}

int	frame(t_controls *controls)
{
	player_update_z_position();
	player_update_position(controls);
	controls->mouse_left = false;
	controls->mouse_right = false;
	data()->player.turn_speed = TURN_STEP;
	rays_create();
	walls_draw_to_image();
	if (MINIMAP_ENABLED)
		minimap_draw_to_image();
	frame_set_up_window();
	return (EXIT_SUCCESS);
}
