# include "cub3d.h"

static bool	static_is_wall(float y, float x)
{
	if (y < data()->map.height && x < data()->map.width)
	{
		if (data()->map.grid[(int)y][(int)x] != WALL)
			return (false);
	}
	return (true);
}

static void	static_update_pos(t_keys *keys)
{
	if (keys->forwards)
	{
		if (!static_is_wall(data()->player.y, (data()->player.x + data()->player.dx * DISTANCE_FACTOR)))
			data()->player.x += data()->player.dx;
		if (!static_is_wall((data()->player.y + data()->player.dy * DISTANCE_FACTOR), data()->player.x))
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
	if (keys->backwards)
	{
		if (!static_is_wall(data()->player.y, (data()->player.x - data()->player.dx)))
			data()->player.x -= data()->player.dx;
		if (!static_is_wall((data()->player.y - data()->player.dy), data()->player.x))
			data()->player.y -= data()->player.dy;
	}
	if (keys->turnright)
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
	fps_display();
	return (EXIT_SUCCESS);
}
