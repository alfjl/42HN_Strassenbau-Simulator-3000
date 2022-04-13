# include "cub3d.h"

static t_ray	static_fill_ray_struct(t_ray ray, int index)
{
	ray.index = index;
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x) + (ray.y - data()->player.y) * (ray.y - data()->player.y));
	float	delta;
	delta = limit_to_radian(data()->player.angle - ray.angle);
	ray.dist = ray.len * cos(delta);
	return (ray);
}

static void		static_iterate(t_ray *ray)
{
	int i = 0;
	while (i < DEPTH_OF_FIELD)
	{
		if ((*ray).y >= 0 && (*ray).x >= 0 && (*ray).y < data()->map.height && (*ray).x < data()->map.width && data()->map.grid[(int)(*ray).y][(int)(*ray).x] == WALL)
			break ;
		else
		{
			(*ray).x += (*ray).dx;
			(*ray).y += (*ray).dy;
			i++;
		}
	}
}

t_ray	ray_calculate_vertical(float angle, int index)
{
	t_ray	ray;
	float	nTan;

	ray.angle = angle;
	nTan = -tan(ray.angle);
	if (ray.angle > PI1 && ray.angle < PI3)
	{
		ray.orientation = WEST;
		ray.x = (float)trunc(data()->player.x) - EDGE;
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = -1;
		ray.dy = -ray.dx * nTan;
		static_iterate(&ray);
	}
	if (ray.angle < PI1 || ray.angle > PI3)
	{
		ray.orientation = EAST;
		ray.x = (float)ceil(data()->player.x);
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = 1;
		ray.dy = -ray.dx * nTan;
		static_iterate(&ray);
	}
	return (static_fill_ray_struct(ray, index));
}

t_ray	ray_calculate_horizontal(float angle, int index)
{
	t_ray	ray;
	float	aTan;
	
	ray.angle = angle;
	aTan = -1 / tan(ray.angle);
	if (ray.angle > PI)
	{
		ray.orientation = NORTH;
		ray.y = (float)trunc(data()->player.y) - EDGE;
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = -1;
		ray.dx = -ray.dy * aTan;
		static_iterate(&ray);
	}
	if (ray.angle < PI)
	{
		ray.orientation = SOUTH;
		ray.y = (float)ceil(data()->player.y);
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = 1;
		ray.dx = -ray.dy * aTan;
		static_iterate(&ray);
	}
	return (static_fill_ray_struct(ray, index));
}
