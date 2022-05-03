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
