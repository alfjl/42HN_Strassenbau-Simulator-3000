/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanghan <alanghan@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:17:17 by alanghan          #+#    #+#             */
/*   Updated: 2022/04/30 19:15:17 by alanghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ----------------------------- FUNC 1 ------------------------------------ */
bool	validation_typecheck_cub(const char *path)
{
	unsigned int	length;

	if (path == NULL)
		return (false);
	length = ft_strlen(path);
	if (
		length < 5
		|| path[length - 4] != '.'
		|| path[length - 3] != 'c'
		|| path[length - 2] != 'u'
		|| path[length - 1] != 'b'
	)
		return (false);
	else
		return (true);
}

/* ----------------------------- FUNC 2 ------------------------------------ */
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

/* ------------------------------ FUNC 3 ----------------------------------- */
bool	validation_check_boolian(bool boolian, int *errorcode, int code)
{
	if (boolian == true)
		return (true);
	*errorcode = code;
	return (false);
}

/* ------------------------------ FUNC 4 ----------------------------------- */
unsigned int	calculate_rgb_value(unsigned int *rgb, unsigned int r,
										unsigned int g, unsigned int b)
{
	*rgb = (r << 16) | (g << 8) | (b);
	return (*rgb);
}
