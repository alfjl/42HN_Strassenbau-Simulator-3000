/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:10 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:33:20 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ----------------------------------- */
bool	reader_has_content(t_reader *reader)
{
	bool	return_value;

	return_value = true;
	if (reader->current >= reader->string_end)
		return_value = false;
	return (return_value);
}

/* ----------------------------- FUNC 2 ----------------------------------- */
bool	reader_read_unsigned_integer(t_reader *reader, unsigned int *target)
{
	bool				return_value;
	unsigned long long	temp;

	return_value = true;
	temp = 0;
	if (reader_peek_char(reader) == '\n' )
		return_value = false;
	else
	{
		temp = ft_atoull(reader->current);
		if (temp > UINT_MAX)
			return_value = false;
		else
		{
			*target = temp;
			if (reader_peek_char(reader) == '+')
				reader->current++;
			while (ft_isdigit(*reader->current) == true
				&& reader->current <= reader->string_end)
				reader->current++;
		}
	}
	return (return_value);
}
