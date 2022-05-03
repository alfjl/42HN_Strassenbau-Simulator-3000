/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:10 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:32:05 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------
** string needs to be null terminated
*/
void	reader_init(t_reader *reader, char *string)
{
	int	i;

	reader->string = string;
	reader->current = string;
	if (reader == NULL || string == NULL)
		return ;
	i = 0;
	while (string[i] != '\0')
		i++;
	reader->string_end = &string[i];
}

/* ----------------------------- FUNC 2 ------------------------------------ */
char	*reader_get_current(t_reader *reader)
{
	return (reader->current);
}

/* ----------------------------- FUNC 3 ------------------------------------ */
void	reader_reset_current(t_reader *reader)
{
	reader->current = reader->string;
}

/* ----------------------------- FUNC 4 ------------------------------------ */
void	reader_increment(t_reader *reader)
{
	if (reader->current < reader->string_end)
		reader->current++;
}

/* ----------------------------- FUNC 5 ------------------------------------ */
void	reader_decrement(t_reader *reader)
{
	if (reader->current > reader->string)
		reader->current--;
}
