/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:29 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:33:48 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
void	stringbuilder_init(t_stringbuilder *builder)
{
	builder->buffer = ft_calloc(BUFFER_SIZE_BUILDER, sizeof(char));
	if (builder->buffer == NULL)
		builder->write_head = 0;
	else
		builder->write_head = BUFFER_SIZE_BUILDER;
	builder->read_head = 0;
}

/* ----------------------------- FUNC 2 ------------------------------------ */
void	stringbuilder_destroy(t_stringbuilder *builder)
{
	if (builder->buffer != NULL)
		free(builder->buffer);
	builder->buffer = NULL;
	builder->read_head = 0;
	builder->write_head = 0;
}

/* ----------------------------- FUNC 3 ------------------------------------ */
bool	stringbuilder_append_char(t_stringbuilder *builder, const char c)
{
	char	*temp;
	int		i;

	if (builder->read_head >= builder->write_head)
	{
		temp = (char *)ft_calloc(builder->read_head + BUFFER_SIZE_BUILDER,
				sizeof(char));
		if (temp == NULL)
			return (false);
		else
		{
			i = 0;
			while (i < builder->read_head)
			{
				temp[i] = builder->buffer[i];
				i++;
			}
			free(builder->buffer);
			builder->buffer = NULL;
			builder->buffer = temp;
			builder->write_head = builder->read_head + BUFFER_SIZE_BUILDER;
		}
	}
	builder->buffer[builder->read_head++] = c;
	return (true);
}

/* ----------------------------- FUNC 4 ------------------------------------ */
bool	stringbuilder_trim_buffer(t_stringbuilder *builder)
{
	char	*temp;
	int		i;

	temp = (char *)ft_calloc(builder->read_head + 1, sizeof(char));
	if (temp == NULL)
		return (false);
	else
	{
		i = 0;
		while (i < builder->read_head)
		{
			temp[i] = builder->buffer[i];
			i++;
		}
		free(builder->buffer);
		builder->buffer = NULL;
		builder->buffer = temp;
		builder->write_head = builder->read_head + 1;
		builder->read_head = 0;
	}
	return (true);
}
