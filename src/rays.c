#include "cub3d.h"

static t_ray	static_ray_get(float angle)
{
	t_ray	ray_horizontal;
	t_ray	ray_vertical;

	ray_horizontal = rays_calculate_horizontal(angle);
	ray_vertical = rays_calculate_vertical(angle);
	if (ray_horizontal.len < ray_vertical.len)
		return (ray_horizontal);
	else
		return (ray_vertical);
}

static void	static_ray_fill_struct(float angle, int i)
{
	float	delta;
	t_ray	*ray;
	t_frame	*window;

	ray = data()->rays;
	window = &data()->window;
	ray[i] = static_ray_get(angle);
	ray[i].index = i;
	delta = radian_limits(data()->player.angle - ray[i].angle);
	ray[i].dist = ray[i].len * cos(delta);
	ray[i].line_h = (window->height / ray[i].dist) * window->width
		/ window->height * ANGLE_OF_VIEW_CONST / ANGLE_OF_VIEW
		* WALL_HEIGHT_RATIO;
}

void	rays_create(void)
{
	int		i;
	float	angle;

	angle = radian_limits(data()->player.angle
			- ANGLE_OF_VIEW / 2 * ONE_DEGREE_IN_RAD);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_ray_fill_struct(angle, i);
		angle = radian_limits(angle
				+ ANGLE_OF_VIEW * ONE_DEGREE_IN_RAD / NUMBER_OF_RAYS);
		i++;
	}
}
