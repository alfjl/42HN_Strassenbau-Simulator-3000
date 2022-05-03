/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:04:15 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:07:40 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ----------------------------------- */
void	config_parse(t_config_file *config, t_map *map)
{
	t_reader		reader;

	reader_init(&reader, config->buffer);
	if (reader.string == NULL)
	{
		config->errorcode = PROBLEM_READING_CONFIG;
		return ;
	}
	while (reader_has_content(&reader) == true && config->map_reached == false
		&& config->errorcode == 0)
		map->spaces = config_header_parse(config, map, &reader);
	config_header_validate(config, map, &config->errorcode);
	if (config->errorcode != 0)
		return ;
	config_map_parse(config, map, &reader, map->spaces);
	if (config->errorcode != 0)
		return ;
	config_map_validate(config, map, &config->errorcode);
}
