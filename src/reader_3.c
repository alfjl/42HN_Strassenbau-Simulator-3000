/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:10 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:33:00 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
unsigned int	reader_skip_whitespace(t_reader *reader)
{
	int		count;
	char	c;

	count = 0;
	c = reader_peek_char(reader);
	while (c != '\n' && reader->current != reader->string_end)
	{
		if (c == ' ')
		{
			reader_increment(reader);
			count++;
		}
		else if (c == '\t')
		{
			reader_increment(reader);
			count += 4;
		}
		else
			break ;
		c = reader_peek_char(reader);
	}
	return (count);
}

/* ----------------------------- FUNC 2 ----------------------------------- */
bool	reader_detect_empty_line(t_reader *reader)
{
	bool	return_value;
	char	*temp;

	temp = reader_get_current(reader);
	return_value = false;
	if (temp != reader->string)
	{
		if (*(temp - 1) == '\n' && *temp == '\n')
			return_value = true;
	}
	if (*temp == '\n')
		return_value = true;
	return (return_value);
}

/* ----------------------------- FUNC 3 ----------------------------------- */
char	*reader_read_to_newline(t_reader *reader)
{
	char			c;
	char			*return_string;
	t_stringbuilder	builder;

	stringbuilder_init(&builder);
	if (builder.buffer == NULL)
		return (NULL);
	while (reader_peek_char(reader) != '\n'
		&& reader->current <= reader->string_end)
	{
		c = reader_read_char(reader);
		if (stringbuilder_append_char(&builder, c) == false)
			return (NULL);
	}
	stringbuilder_trim_buffer(&builder);
	return_string = stringbuilder_return_buffer(&builder);
	return (return_string);
}

/* ----------------------------- FUNC 4 ----------------------------------- */
void	reader_skip_rest_of_line(t_reader *reader)
{
	while (reader_peek_char(reader) != '\n'
		&& reader->current <= reader->string_end)
		reader_increment(reader);
}

/* ----------------------------- FUNC 5 ----------------------------------- */
void	reader_skip_newline(t_reader *reader)
{
	if (reader_peek_char(reader) == '\n')
		reader_increment(reader);
}
