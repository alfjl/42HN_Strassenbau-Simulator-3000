#include "cub3d.h"

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
			color = *(unsigned int *)(src->addr
					+ (unsigned int)((int)y * src->line_len
						+ x * (src->bits_per_pixel / 8))) + ALPHA;
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
			color = *(unsigned int *)(src->addr
					+ (unsigned int)((int)y * src->line_len
						+ x * (src->bits_per_pixel / 8)));
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
