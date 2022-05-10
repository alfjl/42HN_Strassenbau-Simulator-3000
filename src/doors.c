#include "cub3d.h"

static bool	static_doors_is_map_element(float y, float x, int map_element)
{
	if (y < data()->map.height && y >= 0 && x < data()->map.width
		&& x >= 0)
	{
		if (data()->map.grid[(int)y][(int)x] == map_element)
			return (true);
	}
	return (false);
}

void	doors_close_door(void)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	t_ray	*ray;

	ray = &data()->rays[(NUMBER_OF_RAYS - 1) / 2];
	dx = cos(data()->player.angle) * PLAYER_HIT_RANGE;
	dy = sin(data()->player.angle) * PLAYER_HIT_RANGE;
	x = data()->player.x + dx;
	y = data()->player.y + dy;
	if (ray->orientation == NORTH)
		y -= EXTRA_EDGE;
	if (ray->orientation == WEST)
		x -= EXTRA_EDGE;
	if (x < 0 || x >= data()->map.width || y < 0 || y >= data()->map.height)
		return ;
	if (static_doors_is_map_element(y, x, SPACE)
		&& ray->len > pythagoras_hypotenuse(dx, dy))
		data()->map.grid[(int)y][(int)x] = WALL;
}

void	doors_open_door(void)
{
	float	x;
	float	y;
	t_ray	*ray;

	ray = &data()->rays[(NUMBER_OF_RAYS - 1) / 2];
	x = ray->x;
	y = ray->y;
	if (ray->orientation == NORTH)
	{
		x = (int)x;
		y--;
	}
	if (ray->orientation == WEST)
	{
		x--;
		y = (int)y;
	}
	if (ray->len > PLAYER_HIT_RANGE)
		return ;
	if (static_doors_is_map_element(y, x, WALL))
		data()->map.grid[(int)y][(int)x] = SPACE;
}

void	doors_interact(int keycode)
{
	if (keycode == E_KEY)
	{
		data()->player.status = HITTING;
		doors_close_door();
	}
	if (keycode == Q_KEY)
	{
		data()->player.status = HITTING;
		doors_open_door();
	}
}