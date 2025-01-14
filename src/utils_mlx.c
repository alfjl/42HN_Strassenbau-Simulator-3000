/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:55:08 by coder             #+#    #+#             */
/*   Updated: 2022/05/10 11:55:09 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	int	color;

	color = BLACK;
	if (is_inside_image_limits(x, y, img))
	{
		color = *(unsigned int *)(img->addr
				+ (unsigned int)((int)y * img->line_len
					+ x * (img->bits_per_pixel / 8)));
	}
	return (color);
}

void	image_overlay(t_img *src, t_img *dst, int dst_x, int dst_y)
{
	int		x;
	int		y;
	int		color;

	if (src == NULL || dst == NULL || dst->ptr == NULL)
		return ;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = get_pixel_color(src, x, y);
			if (color != (int)TRANSPARENT)
				my_pixel_put(dst, dst_x + x, dst_y + y, color);
			x++;
		}	
		y++;
	}
}

t_img	*image_clone(void *mlx, t_img *src, t_img *dst)
{
	int		x;
	int		y;
	int		color;

	dst->ptr = my_new_image(mlx, src->width, src->height, dst);
	if (dst->ptr == NULL)
		return (NULL);
	y = 0;
	while (y < dst->height)
	{
		x = 0;
		while (x < dst->width)
		{
			color = get_pixel_color(src, x, y);
			my_pixel_put(dst, x, y, color);
			x++;
		}	
		y++;
	}
	return (dst);
}

void	image_fill(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

bool	is_inside_image_limits(int x, int y, t_img *img)
{
	if (x < 0 || x > img->width - 1)
		return (false);
	if (y < 0 || y > img->height - 1)
		return (false);
	return (true);
}
