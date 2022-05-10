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

int	my_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	return (mlx_mouse_hide(mlx_ptr, win_ptr));
}

int	my_mouse_show(void *mlx_ptr, void *win_ptr)
{
	return (mlx_mouse_show(mlx_ptr, win_ptr));
}
#else

int	my_mouse_hide(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (mlx_mouse_hide());
}

int	my_mouse_show(void *mlx_ptr, void *win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	return (mlx_mouse_show());
}
#endif