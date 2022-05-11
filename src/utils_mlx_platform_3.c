/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_platform_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:59 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:55:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#if defined(__linux__)

int	my_destroy_display(void *mlx_ptr)
{
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
#else

int	my_destroy_display(void *mlx_ptr)
{
	free(mlx_ptr);
	return (0);
}
#endif