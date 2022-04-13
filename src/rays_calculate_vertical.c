# include "cub3d.h"

static t_ray	static_fill_ray_struct(t_ray ray, int index)
{
	ray.index = index;
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x) + (ray.y - data()->player.y) * (ray.y - data()->player.y));
	float	delta;
	delta = data()->player.angle - ray.angle;
	if (delta < 0)
		delta += 2 * PI;
	if (delta > 2 * PI)
		delta -= 2 * PI;
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
	if (ray.angle > PI1 && ray.angle < PI3) //looking left
	{
		ray.orientation = WEST;
		ray.x = (float)trunc(data()->player.x) - EDGE;
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = -1;
		ray.dy = -ray.dx * nTan;
		static_iterate(&ray);
	}
	else if (ray.angle < PI1 || ray.angle > PI3) //looking right
	{
		ray.orientation = EAST;
		ray.x = (float)ceil(data()->player.x);
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = 1;
		ray.dy = -ray.dx * nTan;
		static_iterate(&ray);
	}
	else// (ray.angle == 0 || ray.angle == PI) //looking vertical
	{
		ray.x = data()->player.x;
		ray.y = data()->player.y;
	}
	return (static_fill_ray_struct(ray, index));
}
