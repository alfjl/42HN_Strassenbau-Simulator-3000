# include "cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int createRGBA(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
			+ (a & 0xff);
}

unsigned int createARGB(int r, int g, int b, int a)
{
	return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8)
			+ (b & 0xff);
}

static int	static_get_sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

static int	static_abs(int a, int b)
{
	int d;

	d = b - a;
	if (d < 0)
		d *= -1;	
	return (d);
}

void	draw_line_a_to_b (t_img *img, t_point a, t_point b, int color)
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
			break;
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
