#include "cub3d.h"

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

unsigned int	argb_color_shade(int color, float brightness)
{
	int	a;
	int	r;
	int	g;
	int	b;
	a = ((color >> 24) & 0xFF);
	r = ((color >> 16) & 0xFF);
	g = ((color >> 8) & 0xFF);
	b = ((color) & 0xFF);
	return (create_argb(r * brightness, g * brightness, b * brightness, a));
}

void	my_destroy_image(void *mlx_ptr, t_img *img)
{
	if (img->ptr != NULL)
		mlx_destroy_image(mlx_ptr, img->ptr);
	img->ptr = NULL;
}

void	*my_new_image(void *mlx_ptr, int width, int height, t_img *img)
{
	if (LINUX)
		img->ptr = mlx_new_image_alpha(mlx_ptr, width, height);
	else
		img->ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->ptr == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	img->width = width;
	img->height = height;
	image_fill(img, TRANSPARENT);
	return (img->ptr);
}

bool	is_out_of_limits(int x, int y, t_img *img)
{
	if (x < 0 || x > img->width - 1)
		return (true);
	if (y < 0 || y > img->height - 1)
		return (true);
	return (false);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	create_rgba(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (a & 0xff));
}

unsigned int	create_argb(int r, int g, int b, int a)
{
	return (((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8)
		+ (b & 0xff));
}

static int	static_get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

static int	static_abs(int a, int b)
{
	int	d;

	d = b - a;
	if (d < 0)
		d *= -1;
	return (d);
}

float	radian_limits(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	draw_line_a_to_b(t_img *img, t_point a, t_point b, int color)
{
	int	dx;
	int	dy;
	int	err;
	int	e2;

	dx = static_abs(a.x, b.x);
	dy = -static_abs(a.y, b.y);
	err = dx + dy;
	while (1)
	{
		my_pixel_put(img, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			a.x += static_get_sign(a.x, b.x);
		}
		if (e2 <= dx)
		{
			err += dx;
			a.y += static_get_sign(a.y, b.y);
		}
	}
}
