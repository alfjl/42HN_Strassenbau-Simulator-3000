#include "cub3d.h"

void	iterate_grid(t_ray *ray)
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

static void	static_set_ray_parameters_north(t_ray *ray, float atan)
{
	ray->orientation = NORTH;
	ray->y = (float)trunc(data()->player.y) - EDGE;
	ray->x = (data()->player.y - ray->y) * atan + data()->player.x;
	ray->dy = -1;
	ray->dx = -ray->dy * atan;
}

static void	static_set_ray_parameters_south(t_ray *ray, float atan)
{
	ray->orientation = SOUTH;
	ray->y = (float)ceil(data()->player.y);
	ray->x = (data()->player.y - ray->y) * atan + data()->player.x;
	ray->dy = 1;
	ray->dx = -ray->dy * atan;
}

t_ray	ray_calculate_horizontal(float angle)
{
	t_ray	ray;
	float	atan;

	ray.angle = angle;
	atan = -1 / tan(ray.angle);
	if (ray.angle > PI)
		static_set_ray_parameters_north(&ray, atan);
	else if (ray.angle < PI)
		static_set_ray_parameters_south(&ray, atan);
	iterate_grid(&ray);
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x)
			+ (ray.y - data()->player.y) * (ray.y - data()->player.y));
	return (ray);
}
