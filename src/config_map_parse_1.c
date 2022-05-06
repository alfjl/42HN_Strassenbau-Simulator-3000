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
void	config_map_parse_fill_spaces(t_config_file *config,
					t_stringbuilder *builder, unsigned int spaces,
					unsigned int *i)
{
	while (*i < spaces)
	{
		if (stringbuilder_append_char(builder, ' ') == false)
			config->errorcode = SYSTEM;
		*i += 1;
	}
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	config_map_parse_fill_string(t_config_file *config, t_map *map,
									t_reader *reader, t_stringbuilder *builder)
{
	char			c;
	unsigned int	width;

	width = map->spaces;
	while (reader_has_content(reader))
	{
		c = reader_read_char(reader);
		while (c != '\n' && reader_has_content(reader))
		{
			if (stringbuilder_append_char(builder, c) == false)
				config->errorcode = SYSTEM;
			width++;
			c = reader_read_char(reader);
		}
		if (reader_detect_empty_line(reader) == true)
			map->empty_line_flag = true;
		if (stringbuilder_append_char(builder, c) == false)
			config->errorcode = SYSTEM;
		width++;
		config_map_parse_set_width(map, width);
		width = 0;
		map->height++;
	}
	if (stringbuilder_trim_buffer(builder) == false)
		config->errorcode = SYSTEM;
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	config_map_parse_built_grid(t_config_file *config, t_map *map)
{
	unsigned int	i;

	i = 0;
	map->grid = ft_calloc(map->height, sizeof(char *));
	if (map->grid == NULL)
	{
		config->errorcode = SYSTEM;
		return ;
	}
	while (i < map->height)
	{
		map->grid[i] = ft_calloc(map->width, sizeof(char));
		if (map->grid[i] == NULL)
		{
			config->errorcode = SYSTEM;
			break ;
		}
		ft_memset(map->grid[i], VOID, map->width - 1);
		i++;
	}
}

/* ----------------------------- FUNC 4 ------------------------------------ */
void	config_map_parse_read_string_to_grid(t_config_file *config, t_map *map,
												char *string)
{
	t_reader		temp_reader;
	unsigned int	o;
	unsigned int	p;
	char			c;

	reader_init(&temp_reader, string);
	if (temp_reader.string == NULL)
	{
		config->errorcode = PROBLEM_READING_CONFIG;
		return ;
	}
	o = 0;
	while (reader_has_content(&temp_reader))
	{
		p = 0;
		while (p < map->width && reader_has_content(&temp_reader))
		{
			p += reader_skip_whitespace(&temp_reader);
			c = reader_read_char(&temp_reader);
			config_map_parse_set_char(map, o, &p, c);
			p++;
		}
		o++;
	}
}

/* ----------------------------- FUNC 5 ------------------------------------ */
void	config_map_parse(t_config_file *config, t_map *map, t_reader *reader,
							unsigned int spaces)
{
	unsigned int	i;
	t_stringbuilder	builder;
	char			*temp_string;

	i = 0;
	stringbuilder_init(&builder);
	if (builder.buffer == NULL)
	{
		config->errorcode = SYSTEM;
		return ;
	}
	config_map_parse_fill_spaces(config, &builder, spaces, &i);
	config_map_parse_fill_string(config, map, reader, &builder);
	temp_string = stringbuilder_return_buffer(&builder);
	if (config->errorcode == 0 && temp_string != NULL)
	{
		config_map_parse_built_grid(config, map);
		if (config->errorcode == 0)
		{
			config_map_parse_read_string_to_grid(config, map, temp_string);
			map->width -= 1;
		}
	}
	temp_string = NULL;
	stringbuilder_destroy(&builder);
}
