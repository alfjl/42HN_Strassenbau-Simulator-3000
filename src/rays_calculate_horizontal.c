#include "cub3d.h"

static bool	static_rays_hits_map_element(t_ray *ray, t_map *map,
	int map_element)
{
	float	y;
	float	x;

	y = ray->y;
	x = ray->x;
	if (ray->orientation == NORTH)
		y -= EXTRA_EDGE;
	if (ray->orientation == WEST)
		x -= EXTRA_EDGE;
	if (y >= 0 && x >= 0 && y < map->height
		&& x < map->width
		&& map->grid[(int)y][(int)x] == map_element)
		return (true);
	else
		return (false);
}

void	rays_iterate_grid(t_ray *ray)
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
		if (static_rays_hits_map_element(ray, map, WALL))
		{
			ray->is_infinite = false;
			break ;
		}
		else if (BONUS && (ray->x <= 0 || ray->y <= 0
				|| ray->x >= map->width || ray->y >= map->height))
			break ;
		else
		{
			ray->x += ray->dx;
			ray->y += ray->dy;
		}
		i++;
	}
}

static void	static_rays_set_parameters_north(t_ray *ray, float atan)
{
	ray->orientation = NORTH;
	ray->y = trunc(data()->player.y);
	ray->x = (data()->player.y - ray->y) * atan + data()->player.x;
	ray->dy = -1;
	ray->dx = -ray->dy * atan;
}

static void	static_rays_set_parameters_south(t_ray *ray, float atan)
{
	ray->orientation = SOUTH;
	ray->y = ceil(data()->player.y);
	ray->x = (data()->player.y - ray->y) * atan + data()->player.x;
	ray->dy = 1;
	ray->dx = -ray->dy * atan;
}

t_ray	rays_calculate_horizontal(float angle)
{
	t_ray	ray;
	float	atan;

	ray.is_infinite = true;
	ray.angle = angle;
	atan = -1 / tan(ray.angle);
	if (ray.angle > M_PI)
		static_rays_set_parameters_north(&ray, atan);
	else if (ray.angle < M_PI)
		static_rays_set_parameters_south(&ray, atan);
	rays_iterate_grid(&ray);
	ray.len = pythagoras_hypotenuse((ray.x - data()->player.x),
			(ray.y - data()->player.y));
	return (ray);
}
