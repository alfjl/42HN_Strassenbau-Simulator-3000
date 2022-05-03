/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_header_validate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:27:11 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 19:41:23 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
bool	config_header_validate_rgb_values(t_color color)
{
	bool	return_value;

	return_value = true;
	if (color.r > 255
		|| color.g > 255
		|| color.b > 255)
		return_value = false;
	return (return_value);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
bool	config_header_validate_texture_file(const char *path)
{
	bool	return_value;
	int		fd;

	return_value = true;
	if (validation_typecheck_xpm(path) == false)
		return_value = false;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return_value = false;
	close(fd);
	return (return_value);
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	config_header_validate(t_config_file *config,
								t_map *map, int *errorcode)
{
	if (config->north != 1 || config->south != 1 || config->east != 1
		|| config->west != 1 || config->ceiling != 1 || config->floor != 1)
		*errorcode = WRONG_CONFIG_ARGS;
	else if (config_header_validate_texture_file(map->textures.north) == false
		|| config_header_validate_texture_file(map->textures.south) == false
		|| config_header_validate_texture_file(map->textures.east) == false
		|| config_header_validate_texture_file(map->textures.west) == false)
		*errorcode = PROBLEM_READING_TEXTURE;
	else if (config_header_validate_rgb_values(map->ceiling) == false
		|| config_header_validate_rgb_values(map->floor) == false)
		*errorcode = WRONG_RGB_VALUES;
}
