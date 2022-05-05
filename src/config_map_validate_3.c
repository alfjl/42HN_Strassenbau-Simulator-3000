/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_validate_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:13:25 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:01:28 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ----------------------------------- */
bool	config_map_validate_char_walls(t_map *map, char potential_wall)
{
	bool	return_value;
	int		i;

	i = 0;
	return_value = false;
	while (map->walls[i])
	{
		if (map->walls[i] == potential_wall)
			return_value = true;
		i++;
	}
	return (return_value);
}

/* ----------------------------- FUNC 2 ----------------------------------- */
bool	config_map_validate_char_playerpositions(t_map *map, char position)
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

/* ----------------------------- FUNC 3 ----------------------------------- */
bool	config_map_validate_char_space_neighbours(t_map *map, char neighbour)
{
	if (neighbour == SPACE
		|| config_map_validate_char_walls(map, neighbour) == true
		|| config_map_validate_char_playerpositions(map, neighbour) == true)
		return (true);
	return (false);
}

/* ----------------------------- FUNC 4 ----------------------------------- */
bool	config_map_validate_char_player_neighbours(t_map *map,
											unsigned int x, unsigned int y)
{
	if (x == 0 || x == map->height - 1
		|| y == 0 || y == map->width - 1)
		return (false);
	if (
		config_map_validate_char_space_neighbours(map,
			map->grid[x][y - 1]) != true
		|| config_map_validate_char_space_neighbours(map,
			map->grid[x][y + 1]) != true
		|| config_map_validate_char_space_neighbours(map,
			map->grid[x - 1][y]) != true
		|| config_map_validate_char_space_neighbours(map,
			map->grid[x + 1][y]) != true
		)
		return (false);
	return (true);
}
