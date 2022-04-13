#include "cub3d.h"

static void	static_iterate(t_ray *ray)
{
	int		i;
	t_map	*map;

	map = &data()->map;
	i = 0;
	while (i < DEPTH_OF_FIELD)
	{
		if ((*ray).y >= 0 && (*ray).x >= 0 && (*ray).y < map->height
			&& (*ray).x < map->width
			&& map->grid[(int)(*ray).y][(int)(*ray).x] == WALL)
			break ;
		else
		{
			(*ray).x += (*ray).dx;
			(*ray).y += (*ray).dy;
			i++;
		}
	}
}

t_ray	ray_calculate_vertical(float angle)
{
	t_ray	ray;
	float	ntan;

	ray.angle = angle;
	ntan = -tan(ray.angle);
	if (ray.angle > PI1 && ray.angle < PI3)
	{
		ray.orientation = WEST;
		ray.x = (float)trunc(data()->player.x) - EDGE;
		ray.y = (data()->player.x - ray.x) * ntan + data()->player.y;
		ray.dx = -1;
		ray.dy = -ray.dx * ntan;
		static_iterate(&ray);
	}
	if (ray.angle < PI1 || ray.angle > PI3)
	{
		ray.orientation = EAST;
		ray.x = (float)ceil(data()->player.x);
		ray.y = (data()->player.x - ray.x) * ntan + data()->player.y;
		ray.dx = 1;
		ray.dy = -ray.dx * ntan;
		static_iterate(&ray);
	}
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x)
			+ (ray.y - data()->player.y) * (ray.y - data()->player.y));
	return (ray);
}

t_ray	ray_calculate_horizontal(float angle)
{
	t_ray	ray;
	float	atan;

	ray.angle = angle;
	atan = -1 / tan(ray.angle);
	if (ray.angle > PI)
	{
		ray.orientation = NORTH;
		ray.y = (float)trunc(data()->player.y) - EDGE;
		ray.x = (data()->player.y - ray.y) * atan + data()->player.x;
		ray.dy = -1;
		ray.dx = -ray.dy * atan;
		static_iterate(&ray);
	}
	if (ray.angle < PI)
	{
		ray.orientation = SOUTH;
		ray.y = (float)ceil(data()->player.y);
		ray.x = (data()->player.y - ray.y) * atan + data()->player.x;
		ray.dy = 1;
		ray.dx = -ray.dy * atan;
		static_iterate(&ray);
	}
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x)
			+ (ray.y - data()->player.y) * (ray.y - data()->player.y));
	return (ray);
}
