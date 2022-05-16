/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:53:57 by coder             #+#    #+#             */
/*   Updated: 2022/05/16 09:59:39 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	static_player_set_status(t_controls *controls)
{
	t_player	*player;	

	player = &data()->player;
	if (player->status == HITTING)
		return ;
	else if (controls->forwards || controls->backwards || controls->leftwards
		|| controls->rightwards)
		player->status = WALKING;
	else
		player->status = IDLE;
}

static bool	static_is_map_element(float y, float x, int map_element)
{
	float	min_y;
	float	max_y;
	float	min_x;
	float	max_x;
	t_map	*map;

	map = &data()->map;
	min_y = y - COLLISION_DISTANCE;
	max_y = y + COLLISION_DISTANCE;
	min_x = x - COLLISION_DISTANCE;
	max_x = x + COLLISION_DISTANCE;
	if (max_y < map->height && min_y >= 0 && max_x < map->width
		&& min_x >= 0)
	{
		if (map->grid[(int)min_y][(int)min_x] == map_element)
			return (true);
		if (map->grid[(int)max_y][(int)max_x] == map_element)
			return (true);
		if (map->grid[(int)min_y][(int)max_x] == map_element)
			return (true);
		if (map->grid[(int)max_y][(int)min_x] == map_element)
			return (true);
		return (false);
	}
	return (true);
}

static bool	static_is_valid_move(float y, float x)
{
	if (static_is_map_element(y, x, VOID))
		return (false);
	if (!COLLISION_ENABLED)
		return (true);
	else if (static_is_map_element(y, x, WALL))
		return (false);
	return (true);
}

static void	static_player_update_pos(float *x, float dx, float *y, float dy)
{
	float	new_x;
	float	new_y;
	t_map	*map;

	map = &data()->map;
	new_x = *x + dx;
	new_y = *y + dy;
	if (static_is_valid_move(*y, (*x + dx)))
	{
		if (new_x >= 0 && new_x < map->width)
			*x = new_x;
	}
	if (static_is_valid_move((*y + dy), *x))
	{
		if (new_y >= 0 && new_y < map->height)
			*y = new_y;
	}
}

void	player_move(t_controls *controls)
{
	t_player	*player;
	float		*x;
	float		*y;
	float		dx;
	float		dy;

	player = &data()->player;
	calculate_pos_delta();
	x = &player->x;
	y = &player->y;
	dx = player->dx;
	dy = player->dy;
	if (controls->forwards)
		static_player_update_pos(x, dx, y, dy);
	if (controls->backwards)
		static_player_update_pos(x, -dx, y, -dy);
	if (controls->leftwards)
		static_player_update_pos(x, dy, y, -dx);
	if (controls->rightwards)
		static_player_update_pos(x, -dy, y, dx);
	if (controls->turnleft || controls->mouse_left)
		player->angle = radian_limits(player->angle - player->turn_speed);
	if (controls->turnright || controls->mouse_right)
		player->angle = radian_limits(player->angle + player->turn_speed);
	static_player_set_status(controls);
}
