/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:07:17 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:12:21 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	map_init(t_map *map)
{
	map->empty_line_flag = false;
	map->grid = NULL;
	map->walls[0] = WALL;
	map->walls[1] = '\0';
	map->player_pos[0] = PLAYER_NORTH;
	map->player_pos[1] = PLAYER_SOUTH;
	map->player_pos[2] = PLAYER_EAST;
	map->player_pos[3] = PLAYER_WEST;
	map->player_pos[4] = '\0';
	map->height = 0;
	map->width = 0;
	map->spaces = 0;
	color_init(&map->ceiling);
	color_init(&map->floor);
	textures_init(&map->textures);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	map_destroy(t_map *map)
{
	unsigned int	i;

	i = 0;
	if (map->grid != NULL)
	{
		while (i < map->height && map->grid[i] != NULL)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	textures_destroy(&map->textures);
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	player_init(t_player *player)
{
	player->x = 0.0f;
	player->y = 0.0f;
	player->dx = 0.0f;
	player->dy = 0.0f;
	player->angle = 0.0f;
	data()->player.status = IDLE;
	data()->player.step_size = MOVE_STEP;
	data()->player.turn_speed = TURN_STEP;
	data()->player.dz = 0;
	data()->player.is_jumping = false;
	data()->player.is_crouching = false;
}

/* ----------------------------- FUNC 4 ------------------------------------ */
void	player_set_values(t_player *player, t_map *map, int x, int y)
{
	player->x = (float)y + 0.5;
	player->y = (float)x + 0.5;
	calculate_pos_delta();
	player->angle = player_calculate_angle(map->grid[x][y]);
}
