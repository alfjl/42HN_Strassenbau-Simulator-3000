/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:10 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:32:27 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	reader_increment_stepsize(t_reader *reader, unsigned int steps)
{
	unsigned int	i;

	i = 0;
	while (i < steps)
	{
		reader_increment(reader);
		i++;
	}
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	reader_decrement_stepsize(t_reader *reader, unsigned int steps)
{
	unsigned int	i;

	i = 0;
	while (i < steps)
	{
		reader_decrement(reader);
		i++;
	}
}

/* ----------------------------- FUNC 3 ------------------------------------ */
char	reader_peek_char(t_reader *reader)
{
	return (*reader->current);
}

/* ----------------------------- FUNC 4 ------------------------------------
** returns a char and increments reader->current
*/
char	reader_read_char(t_reader *reader)
{
	char	c;

	c = *reader->current;
	if (reader->current < reader->string_end)
		reader_increment(reader);
	return (c);
}

/* ----------------------------- FUNC 5 ------------------------------------
** string needs to be null terminated
*/
bool	reader_peek_string(t_reader *reader, const char *string)
{
	bool	return_value;
	char	*current_char;

	return_value = true;
	current_char = reader->current;
	while (*string != '\0' && current_char != reader->string_end)
	{
		if (*string != *current_char)
		{
			return_value = false;
			break ;
		}
		string++;
		current_char++;
	}
	return (return_value);
}
