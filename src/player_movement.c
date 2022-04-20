#include "cub3d.h"

static bool	static_is_wall(float y, float x)
{
	float	min_y;
	float	max_y;
	float	min_x;
	float	max_x;

	if (!COLLISION)
		return (false);
	min_y = y - DISTANCE;
	max_y = y + DISTANCE;
	min_x = x - DISTANCE;
	max_x = x + DISTANCE;
	if (max_y < data()->map.height && min_y >= 0 && max_x < data()->map.width
		&& min_x >= 0)
	{
		if (data()->map.grid[(int)min_y][(int)min_x] == WALL)
			return (true);
		if (data()->map.grid[(int)max_y][(int)max_x] == WALL)
			return (true);
		if (data()->map.grid[(int)min_y][(int)max_x] == WALL)
			return (true);
		if (data()->map.grid[(int)max_y][(int)min_x] == WALL)
			return (true);
		return (false);
	}
	return (true);
}

static void	static_player_update(float *x, float dx, float *y, float dy)
{
	float	new_x;
	float	new_y;
	t_map	*map;

	map = &data()->map;
	new_x = *x + dx;
	new_y = *y + dy;
	if (!static_is_wall(*y, (*x + dx)))
	{
		if (new_x >= 0 && new_x < map->width)
			*x = new_x;
	}
	if (!static_is_wall((*y + dy), *x))
	{
		if (new_y >= 0 && new_y < map->height)
			*y = new_y;
	}
}

void	player_update_position(t_keys *keys)
{
	t_player	*player;
	float		*x;
	float		*y;
	float		dx;
	float		dy;

	player = &data()->player;
	player->dx = cos(player->angle) * STEP;
	player->dy = sin(player->angle) * STEP;
	x = &player->x;
	y = &player->y;
	dx = player->dx;
	dy = player->dy;
	if (keys->forwards)
		static_player_update(x, dx, y, dy);
	if (keys->backwards)
		static_player_update(x, -dx, y, -dy);
	if (keys->leftwards)
		static_player_update(x, dy, y, -dx);
	if (keys->rightwards)
		static_player_update(x, -dy, y, dx);
	if (keys->turnleft)
		player->angle = radian_limits(player->angle - STEP_A);
	if (keys->turnright)
		player->angle = radian_limits(player->angle + STEP_A);
}
