/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringbuilder_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:08:18 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 18:58:07 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
char	*stringbuilder_return_buffer(t_stringbuilder *builder)
{
	return (builder->buffer);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
int	stringbuilder_return_write_head(t_stringbuilder *builder)
{
	return (builder->write_head);
}

/* ----------------------------- FUNC 3 ------------------------------------ */
int	stringbuilder_return_read_head(t_stringbuilder *builder)
{
	return (builder->read_head);
}

/* ----------------------------- FUNC 4 ------------------------------------ */
char	*stringbuilder_trim_and_return_buffer(t_stringbuilder *builder)
{
	char	*return_string;

	stringbuilder_trim_buffer(builder);
	return_string = stringbuilder_return_buffer(builder);
	return (return_string);
}
