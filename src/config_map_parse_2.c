/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:13:51 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 13:13:52 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	config_map_parse_set_null(t_map *map, unsigned int o, unsigned int *p)
{
	while (*p < map->width - 1)
		*p += 1;
	map->grid[o][*p] = '\0';
}			

/* ----------------------------- FUNC 2 ------------------------------------ */
void	config_map_parse_set_char(t_map *map, unsigned int o, unsigned int *p,
									char c)
{
	if (c == '\n')
		config_map_parse_set_null(map, o, p);
	else
		map->grid[o][*p] = c;
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	config_map_parse_set_width(t_map *map, unsigned int width)
{
		if (width > map->width)
			map->width = width;
}

