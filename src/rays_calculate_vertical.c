/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calculate_vertical.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:11 by coder             #+#    #+#             */
/*   Updated: 2022/05/16 10:04:30 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_rays_set_parameters_east(t_ray *ray, float ntan,
	t_player *player)
{
	ray->orientation = EAST;
	ray->x = ceil(player->x);
	ray->y = (player->x - ray->x) * ntan + player->y;
	ray->dx = 1;
	ray->dy = -ray->dx * ntan;
}

static void	static_rays_set_parameters_west(t_ray *ray, float ntan,
	t_player *player)
{
	ray->orientation = WEST;
	ray->x = trunc(player->x);
	ray->y = (player->x - ray->x) * ntan + player->y;
	ray->dx = -1;
	ray->dy = -ray->dx * ntan;
}

t_ray	rays_calculate_vertical(float angle)
{
	t_ray		ray;
	float		ntan;
	t_player	*player;

	player = &data()->player;
	ray.is_infinite = true;
	ray.angle = angle;
	ntan = -tan(ray.angle);
	if (ray.angle > M_PI_2 && ray.angle < (3 * M_PI_2))
		static_rays_set_parameters_west(&ray, ntan, player);
	else if (ray.angle < M_PI_2 || ray.angle > (3 * M_PI_2))
		static_rays_set_parameters_east(&ray, ntan, player);
	rays_iterate_grid(&ray);
	ray.len = pythagoras_hypotenuse((ray.x - player->x),
			(ray.y - player->y));
	return (ray);
}
