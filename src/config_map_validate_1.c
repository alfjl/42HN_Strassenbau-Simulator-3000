/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_validate_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:14:35 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:04:20 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ----------------------------------- */
void	config_map_validate(t_config_file *config, t_map *map, int *errorcode)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	if (validation_check_boolian(config->map_reached, errorcode,
			INVALID_MAP) == false)
		return ;
	while (x < map->height && config->map_reached == true)
	{
		y = 0;
		while (map->grid[x][y] != '\0')
		{
			if (map->empty_line_flag == true
				|| config_map_validate_char(config, map, x, y) != true)
			{
				*errorcode = INVALID_MAP;
				break ;
			}
			y++;
		}
		if (*errorcode != 0)
			break ;
		x++;
	}
	validation_check_boolian(config->player_position, errorcode, INVALID_MAP);
}
