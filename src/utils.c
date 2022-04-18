#include "cub3d.h"

void	*my_new_image(void *mlx_ptr, int width, int height, t_img *img)
{
	img->ptr = mlx_new_image_alpha(mlx_ptr, width, height);
	if (img->ptr == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = width;
	img->height = height;
	return (img->ptr);
}

bool	pixel_is_outside_img_limits(int x, int y, t_img *img)
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

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
