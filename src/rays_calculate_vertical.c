#include "cub3d.h"

static void	static_set_ray_parameters_east(t_ray *ray, float ntan)
{
	ray->orientation = EAST;
	ray->x = (float)ceil(data()->player.x);
	ray->y = (data()->player.x - ray->x) * ntan + data()->player.y;
	ray->dx = 1;
	ray->dy = -ray->dx * ntan;
}

static void	static_set_ray_parameters_west(t_ray *ray, float ntan)
{
	ray->orientation = WEST;
	ray->x = (float)trunc(data()->player.x) - EDGE;
	ray->y = (data()->player.x - ray->x) * ntan + data()->player.y;
	ray->dx = -1;
	ray->dy = -ray->dx * ntan;
}

t_ray	ray_calculate_vertical(float angle)
{
	t_ray	ray;
	float	ntan;

	ray.angle = angle;
	ntan = -tan(ray.angle);
	if (ray.angle > PI1_2 && ray.angle < PI3_2)
		static_set_ray_parameters_west(&ray, ntan);
	else if (ray.angle < PI1_2 || ray.angle > PI3_2)
		static_set_ray_parameters_east(&ray, ntan);
	iterate_grid(&ray);
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x)
			+ (ray.y - data()->player.y) * (ray.y - data()->player.y));
	return (ray);
}
