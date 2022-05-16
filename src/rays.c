/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:14 by coder             #+#    #+#             */
/*   Updated: 2022/05/16 10:06:35 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	static_ray_fill_struct(t_ray *rays, float angle, int i)
{
	float	delta;
	t_frame	*window;

	window = &data()->window;
	rays[i] = static_ray_get(angle);
	rays[i].index = i;
	delta = radian_limits(data()->player.angle - rays[i].angle);
	rays[i].dist = rays[i].len * cos(delta);
	rays[i].line_h = (window->height / rays[i].dist) * window->width
		/ window->height * ANGLE_OF_VIEW_CONST / ANGLE_OF_VIEW
		* WALL_HEIGHT_RATIO;
}

void	rays_create(void)
{
	int		i;
	float	angle;
	t_ray	*rays;

	rays = data()->rays;
	angle = radian_limits(data()->player.angle
			- ANGLE_OF_VIEW / 2 * ONE_DEGREE_IN_RAD);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_ray_fill_struct(rays, angle, i);
		angle = radian_limits(angle
				+ ANGLE_OF_VIEW * ONE_DEGREE_IN_RAD / NUMBER_OF_RAYS);
		i++;
	}
}
