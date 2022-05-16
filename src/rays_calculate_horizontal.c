/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calculate_horizontal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:02 by coder             #+#    #+#             */
/*   Updated: 2022/05/16 10:03:07 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	static_rays_hits_map_element(t_ray *ray, t_map *map,
	int map_element)
{
	float	y;
	float	x;

	y = ray->y;
	x = ray->x;
	if (ray->angle > M_PI_2 && ray->angle < (3 * M_PI_2))
		x = (int)(x - EXTRA_EDGE);
	if (ray->angle > M_PI)
		y = (int)(y - EXTRA_EDGE);
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
		else if ((ray->x <= 0 || ray->y <= 0
				|| ray->x >= map->width || ray->y >= map->height))
			break ;
		ray->x += ray->dx;
		ray->y += ray->dy;
		i++;
	}
}

static void	static_rays_set_parameters_north(t_ray *ray, float atan,
	t_player *player)
{
	ray->orientation = NORTH;
	ray->y = trunc(player->y);
	ray->x = (player->y - ray->y) * atan + player->x;
	ray->dy = -1;
	ray->dx = -ray->dy * atan;
}

static void	static_rays_set_parameters_south(t_ray *ray, float atan,
	t_player *player)
{
	ray->orientation = SOUTH;
	ray->y = ceil(player->y);
	ray->x = (player->y - ray->y) * atan + player->x;
	ray->dy = 1;
	ray->dx = -ray->dy * atan;
}

t_ray	rays_calculate_horizontal(float angle)
{
	t_ray		ray;
	float		atan;
	t_player	*player;

	player = &data()->player;
	ray.is_infinite = true;
	ray.angle = angle;
	atan = -1 / tan(ray.angle);
	if (ray.angle > M_PI)
		static_rays_set_parameters_north(&ray, atan, player);
	else if (ray.angle < M_PI)
		static_rays_set_parameters_south(&ray, atan, player);
	rays_iterate_grid(&ray);
	ray.len = pythagoras_hypotenuse((ray.x - player->x),
			(ray.y - player->y));
	return (ray);
}
