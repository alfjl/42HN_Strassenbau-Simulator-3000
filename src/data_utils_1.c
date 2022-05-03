/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:07:17 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:11:04 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	color_init(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
	color->rgb = 0;
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	textures_init(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	textures_destroy(t_textures *textures)
{
	if (textures->north != NULL)
		free(textures->north);
	if (textures->south != NULL)
		free(textures->south);
	if (textures->east != NULL)
		free(textures->east);
	if (textures->west != NULL)
		free(textures->west);
}

/* ----------------------------- FUNC 4 ------------------------------------ */
void	config_file_init(t_config_file *config_file)
{
	config_file->map_reached = false;
	config_file->player_position = false;
	config_file->buffer = NULL;
	config_file->read_head = 0;
	config_file->write_head = 0;
	config_file->errorcode = 0;
	config_file->north = 0;
	config_file->south = 0;
	config_file->east = 0;
	config_file->west = 0;
	config_file->ceiling = 0;
	config_file->floor = 0;
}

/* ----------------------------- FUNC 5 ------------------------------------ */
void	config_file_destroy(t_config_file *config_file)
{
	if (config_file->buffer != NULL)
		free(config_file->buffer);
}
