/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_header_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:13:45 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:07:06 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
bool	static_config_header_check_comma(t_config_file *config,
											t_reader *reader)
{
	if (reader_peek_char(reader) != ',')
	{
		config->errorcode = WRONG_CONFIG_ARGS;
		return (false);
	}
	return (true);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
static void	static_config_header_parse_texture(t_config_file *config,
								t_map *map, t_reader *reader, int argument)
{
	reader_increment_stepsize(reader, 2);
	reader_skip_whitespace(reader);
	if (argument == NO && config->north == 0)
	{
		map->textures.north = reader_read_to_newline(reader);
		config->north++;
	}
	else if (argument == SO && config->south == 0)
	{
		map->textures.south = reader_read_to_newline(reader);
		config->south++;
	}
	else if (argument == WE && config->west == 0)
	{
		map->textures.west = reader_read_to_newline(reader);
		config->west++;
	}
	else if (argument == EA && config->east == 0)
	{
		map->textures.east = reader_read_to_newline(reader);
		config->east++;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------ */
static void	static_config_header_parse_ceiling(t_config_file *config,
												t_map *map, t_reader *reader)
{
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->ceiling.r);
	reader_skip_whitespace(reader);
	if (static_config_header_check_comma(config, reader) == false)
		return ;
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->ceiling.g);
	reader_skip_whitespace(reader);
	if (static_config_header_check_comma(config, reader) == false)
		return ;
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->ceiling.b);
	reader_skip_whitespace(reader);
	if (reader_peek_char(reader) != '\n')
		config->errorcode = WRONG_CONFIG_ARGS;
	calculate_rgb_value(&map->ceiling.rgb, map->ceiling.r, map->ceiling.g,
		map->ceiling.b);
	config->ceiling++;
}

/* ----------------------------- FUNC 4 ------------------------------------ */
static void	static_config_header_parse_floor(t_config_file *config,
												t_map *map, t_reader *reader)
{
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->floor.r);
	reader_skip_whitespace(reader);
	if (static_config_header_check_comma(config, reader) == false)
		return ;
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->floor.g);
	reader_skip_whitespace(reader);
	if (static_config_header_check_comma(config, reader) == false)
		return ;
	reader_increment(reader);
	reader_skip_whitespace(reader);
	reader_read_unsigned_integer(reader, &map->floor.b);
	reader_skip_whitespace(reader);
	if (reader_peek_char(reader) != '\n')
		config->errorcode = WRONG_CONFIG_ARGS;
	calculate_rgb_value(&map->floor.rgb, map->floor.r, map->floor.g,
		map->floor.b);
	config->floor++;
}

/* ----------------------------- FUNC 5 ------------------------------------ */
unsigned int	config_header_parse(t_config_file *config, t_map *map,
										t_reader *reader)
{
	unsigned int	spaces;

	spaces = reader_skip_whitespace(reader);
	if (reader_peek_string(reader, "\n"))
		reader_increment(reader);
	else if (reader_peek_string(reader, "NO"))
		static_config_header_parse_texture(config, map, reader, NO);
	else if (reader_peek_string(reader, "SO"))
		static_config_header_parse_texture(config, map, reader, SO);
	else if (reader_peek_string(reader, "WE"))
		static_config_header_parse_texture(config, map, reader, WE);
	else if (reader_peek_string(reader, "EA"))
		static_config_header_parse_texture(config, map, reader, EA);
	else if (reader_peek_string(reader, "C"))
		static_config_header_parse_ceiling(config, map, reader);
	else if (reader_peek_string(reader, "F"))
		static_config_header_parse_floor(config, map, reader);
	else if (reader_peek_string(reader, "1"))
		config->map_reached = true;
	else
		config->errorcode = WRONG_CONFIG_ARGS;
	return (spaces);
}
