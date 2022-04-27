#include "cub3d.h"

void	calculate_pos_delta(void)
{
	t_player	*player;

	player = &data()->player;
	player->dx = cos(player->angle) * player->step_size;
	player->dy = sin(player->angle) * player->step_size;
}

float	radian_limits(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
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
