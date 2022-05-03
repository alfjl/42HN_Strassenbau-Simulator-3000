/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_validate_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:14:40 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:04:20 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ----------------------------------- */
static bool	static_config_map_validate_char_playerpositions(t_map *map,
																char position)
{
	bool	return_value;
	int		i;

	i = 0;
	return_value = false;
	while (map->player_pos[i])
	{
		if (map->player_pos[i] == position)
			return_value = true;
		i++;
	}
	return (return_value);
}

/* ----------------------------- FUNC 2 ----------------------------------- */
static bool	static_config_map_validate_char_space_neighbours(t_map *map,
															char neighbour)
{
	if (neighbour == SPACE
		|| config_map_validate_char_walls(map, neighbour) == true
		|| static_config_map_validate_char_playerpositions(map,
			neighbour) == true)
		return (true);
	return (false);
}

/* ----------------------------- FUNC 3 ----------------------------------- */
static bool	static_config_map_validate_char_space(t_map *map,
											unsigned int x, unsigned int y)
{
	if (x == 0 || x == map->height - 1)
		return (false);
	if (
		static_config_map_validate_char_space_neighbours(map,
			map->grid[x][y - 1]) != true
		|| static_config_map_validate_char_space_neighbours(map,
			map->grid[x][y + 1]) != true
		|| static_config_map_validate_char_space_neighbours(map,
			map->grid[x - 1][y]) != true
		|| static_config_map_validate_char_space_neighbours(map,
			map->grid[x + 1][y]) != true
		)
		return (false);
	return (true);
}

/* ----------------------------- FUNC 4 ----------------------------------- */
static bool	static_config_map_validate_char_player(t_config_file *config,
								t_map *map, unsigned int x, unsigned int y)
{
	t_player	*player;

	player = &data()->player;
	if (config->player_position == true)
		return (false);
	else
	{
		config->player_position = true;
		player_set_values(player, map, x, y);
		map->grid[x][y] = SPACE;
	}
	return (true);
}

/* ----------------------------- FUNC 5 ----------------------------------- */
bool	config_map_validate_char(t_config_file *config, t_map *map,
								unsigned int x, unsigned int y)
{
	if (map->grid[x][y] == SPACE)
	{
		if (static_config_map_validate_char_space(map, x, y) == false)
			return (false);
	}
	else if (static_config_map_validate_char_playerpositions(map,
			map->grid[x][y]))
	{
		if (static_config_map_validate_char_player(config, map, x, y) == false)
			return (false);
	}
	else if (map->grid[x][y] == WALL || map->grid[x][y] == VOID)
		;
	else
		return (false);
	return (true);
}
