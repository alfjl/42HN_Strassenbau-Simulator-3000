/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:17:17 by alanghan          #+#    #+#             */
/*   Updated: 2022/06/01 09:55:56 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
bool	validation_typecheck_cub_extension(unsigned int length,
											char **sections, int i)
{
	if (i > 0)
		i -= 1;
	if (
		length < 5
		|| sections[i][length - 4] != '.'
		|| sections[i][length - 3] != 'c'
		|| sections[i][length - 2] != 'u'
		|| sections[i][length - 1] != 'b'
	)
		return (false);
	else
		return (true);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
bool	validation_typecheck_cub(const char *path)
{
	bool			return_value;
	int				i;
	unsigned int	length;
	char			**sections;

	if (path == NULL)
		return (false);
	sections = ft_split(path, '/');
	if (sections == NULL)
		return (false);
	i = 0;
	while (sections[i])
	{
		length = ft_strlen(sections[i]);
		i++;
	}
	return_value = validation_typecheck_cub_extension(length, sections, i);
	while (i >= 0)
	{
		free(sections[i]);
		i--;
	}
	free(sections);
	return (return_value);
}

/* ----------------------------- FUNC 3 ------------------------------------ */
bool	validation_typecheck_xpm(const char *path)
{
	unsigned int	length;

	if (path == NULL)
		return (false);
	length = ft_strlen(path);
	if (
		length < 5
		|| path[length - 4] != '.'
		|| path[length - 3] != 'x'
		|| path[length - 2] != 'p'
		|| path[length - 1] != 'm'
	)
		return (false);
	else
		return (true);
}

/* ------------------------------ FUNC 4 ----------------------------------- */
bool	validation_check_boolian(bool boolian, int *errorcode, int code)
{
	if (boolian == true)
		return (true);
	*errorcode = code;
	return (false);
}

/* ------------------------------ FUNC 5 ----------------------------------- */
unsigned int	calculate_rgb_value(unsigned int *rgb, unsigned int r,
										unsigned int g, unsigned int b)
{
	*rgb = (r << 16) | (g << 8) | (b);
	return (*rgb);
}
