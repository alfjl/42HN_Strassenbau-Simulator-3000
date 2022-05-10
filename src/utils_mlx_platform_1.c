/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_platform_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:54:55 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:54:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#if defined(__linux__)

int	my_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	return (mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y));
}

int	my_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	return (mlx_mouse_move(mlx_ptr, win_ptr, x, y));
}

#else

int	my_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	return (mlx_mouse_get_pos(win_ptr, x, y));
}

int	my_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	(void)mlx_ptr;
	return (mlx_mouse_move(win_ptr, x, y));
}

#endif