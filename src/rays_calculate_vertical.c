/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calculate_vertical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:11 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:54:12 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_rays_set_parameters_east(t_ray *ray, float ntan)
{
	ray->orientation = EAST;
	ray->x = ceil(data()->player.x);
	ray->y = (data()->player.x - ray->x) * ntan + data()->player.y;
	ray->dx = 1;
	ray->dy = -ray->dx * ntan;
}

static void	static_rays_set_parameters_west(t_ray *ray, float ntan)
{
	ray->orientation = WEST;
	ray->x = trunc(data()->player.x);
	ray->y = (data()->player.x - ray->x) * ntan + data()->player.y;
	ray->dx = -1;
	ray->dy = -ray->dx * ntan;
}

t_ray	rays_calculate_vertical(float angle)
{
	t_ray	ray;
	float	ntan;

	ray.is_infinite = true;
	ray.angle = angle;
	ntan = -tan(ray.angle);
	if (ray.angle > M_PI_2 && ray.angle < (3 * M_PI_2))
		static_rays_set_parameters_west(&ray, ntan);
	else if (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2))
		static_rays_set_parameters_east(&ray, ntan);
	rays_iterate_grid(&ray);
	ray.len = pythagoras_hypotenuse((ray.x - data()->player.x),
			(ray.y - data()->player.y));
	return (ray);
}
