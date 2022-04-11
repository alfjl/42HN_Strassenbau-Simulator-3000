# include "cub3d.h"

static void	static_update_pos(t_keys *keys)
{
	if (keys->forwards)
	{
		data()->player.x += data()->player.dx;
		data()->player.y += data()->player.dy;
	}
	if (keys->turnleft)
	{
		data()->player.angle -= STEP_A;
		if (data()->player.angle < 0)
			data()->player.angle += 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
	if (keys->turnright)
	{
		data()->player.x -= data()->player.dx;
		data()->player.y -= data()->player.dy;
	}
	if (keys->backwards)
	{
		data()->player.angle += STEP_A;
		if (data()->player.angle > 2 * PI)
			data()->player.angle -= 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
}


int	game(t_keys *keys)
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[BACKGROUND_IMG].ptr, 0, 0);
	static_update_pos(keys);
	walls_display();
	minimap_display();
	return (EXIT_SUCCESS);
}
