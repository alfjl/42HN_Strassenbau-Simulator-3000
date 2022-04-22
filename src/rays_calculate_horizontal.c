#include "cub3d.h"

static bool	static_ray_hits_wall(t_ray *ray, t_map *map)
{
	float	y;
	float	x;
	
	y = ray->y;
	x = ray->x;
	if (ray->orientation == NORTH)
		y -= EDGE;
	if (ray->orientation == WEST)
		x -= EDGE;
	if (y >= 0 && x >= 0 && y < map->height
		&& x < map->width
		&& map->grid[(int)y][(int)x] == WALL)
		return (true);
	else
		return  (false);
}

void	iterate_grid(t_ray *ray)
{
	int		i;
	t_map	*map;

	map = &data()->map;
	i = 0;
	while (i < DEPTH_OF_FIELD)
	{
		if (i < MINIMAP_RADIUS + 1)
		{
			ray->mini_x = ray->x;
			ray->mini_y = ray->y;
		}
		if (static_ray_hits_wall(ray, map))
			break ;
		else
		{
			ray->x += ray->dx;
			ray->y += ray->dy;
		}
		i++;
	}
}

static void	static_set_ray_parameters_north(t_ray *ray, float atan)
{
	ray->orientation = NORTH;
	ray->y = (float)trunc(data()->player.y);
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
	if (ray.angle > M_PI)
		static_set_ray_parameters_north(&ray, atan);
	else if (ray.angle < M_PI)
		static_set_ray_parameters_south(&ray, atan);
	iterate_grid(&ray);
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x)
			+ (ray.y - data()->player.y) * (ray.y - data()->player.y));
	return (ray);
}
