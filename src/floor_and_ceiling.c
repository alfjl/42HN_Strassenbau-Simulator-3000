/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:53:24 by coder             #+#    #+#             */
/*   Updated: 2022/05/16 10:08:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	static_get_floor_value(float player_value,
	float ray_value, int y, float wall_dist)
{
	float	current_dist;
	float	weight;
	float	current_floor_value;
	t_frame	*window;

	window = &data()->window;
	current_dist = fabs(window->height / (2.0 * (y - data()->player.dz)
				- window->height - 1));
	weight = current_dist / wall_dist;
	current_floor_value = weight * (ray_value - player_value) * 2
		+ player_value;
	return (current_floor_value);
}

static int	static_get_texture_color(int image, t_ray *ray, int y)
{
	float		map_x;
	float		map_y;
	int			tx;
	int			ty;
	t_player	*player;

	player = &data()->player;
	map_x = static_get_floor_value(player->x,
			ray->x, y, ray->dist);
	map_y = static_get_floor_value(player->y,
			ray->y, y, ray->dist);
	tx = (map_x - (int)map_x) * TEXTURE_SIZE;
	ty = (map_y - (int)map_y) * TEXTURE_SIZE;
	return (get_pixel_color(&data()->imgs[image], tx, ty));
}

int	get_ceiling_color(t_ray *ray, int y)
{
	int	image;

	image = CEILING_IMG;
	if (CEILING_TEXTURE_ENABLED)
		return (static_get_texture_color(image, ray, y));
	else if (SKY_ENABLED)
		return (get_sky_color(ray, y));
	return (data()->map.ceiling.rgb);
}

// static t_point static_get_coordiante(float player_value,
// 	float ray_value, int y, float wall_dist)
// {
// 	t_point	p;

// 	p.x = 0;
// 	p.y = 0;
// 	float	current_dist;
// 	float	weight;
// 	float	current_floor_value;

// 	current_dist = fabs(data()->window.height / (2.0 * (y - data()->player.dz)
// 				- data()->window.height));
// 	weight = current_dist / wall_dist;
// 	current_floor_value = weight * (ray_value - player_value)
// 		+ player_value / 2;
// 	return (p);
// }

static int	static_get_texture(t_ray *ray, int y)
{
	int			map_x;
	int			map_y;
	t_map		*map;
	t_player	*player;

	map = &data()->map;
	player = &data()->player;
	map_x = static_get_floor_value(player->x,
			ray->x, y, ray->dist);
	map_y = static_get_floor_value(player->y,
			ray->y, y, ray->dist);
	if (map_x < 0 || map_x >= (int)map->width
		|| map_y < 0 || map_y >= (int)map->height)
		return (SKY_IMG);
	if (map->grid[map_y][map_x] == SPACE
		|| map->grid[map_y][map_x] == WALL)
		return (FLOOR_IMG);
	return (SKY_IMG);
}

int	get_floor_color(t_ray *ray, int y)
{
	int	image;

	image = static_get_texture(ray, y);
	if (image == SKY_IMG)
		return (get_sky_color(ray, y));
	if (FLOOR_TEXTURE_ENABLED)
		return (static_get_texture_color(image, ray, y));
	return (data()->map.floor.rgb);
}
