#include "cub3d.h"

static int	static_walls_get_texture_image_index(int index)
{
	if (data()->rays[index].orientation == NORTH)
		return (NORTH_IMG);
	else if (data()->rays[index].orientation == SOUTH)
		return (SOUTH_IMG);
	else if (data()->rays[index].orientation == EAST)
		return (EAST_IMG);
	else
		return (WEST_IMG);
}

static int	static_walls_determine_tx(int index)
{
	int		tx;
	t_ray	*ray;

	ray = &data()->rays[index];
	if (ray->orientation == NORTH || ray->orientation == SOUTH)
		tx = (ray->x - (int)ray->x) * TEXTURE_SIZE;
	else
		tx = (ray->y - (int)ray->y) * TEXTURE_SIZE;
	if (ray->orientation == WEST
		|| ray->orientation == SOUTH)
		tx = TEXTURE_SIZE - 1 - tx;
	if (tx < 0)
		tx = 0;
	return (tx);
}

static void	static_get_walls_color(t_img *img, t_point start,
											t_ray *ray, int y)
{
	int		color;
	int		tx;
	float	ty;
	int		image;

	image = static_walls_get_texture_image_index(ray->index);
	tx = static_walls_determine_tx(ray->index);
	ty = ray->tyoffset
		+ (TEXTURE_SIZE / ray->line_h) * (y - start.y);
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void	static_walls_draw_single_vertical_line(t_img *img, t_point start,
													t_point end, t_ray *ray)
{
	int		y;
	int		window_h;

	window_h = data()->window.height;
	y = 0;
	if (HAS_ALPHA)
		y = start.y;
	while (y < window_h)
	{
		if (y < start.y)
			get_ceiling_color(img, start, ray, y);
		else if (y < end.y)
			static_get_walls_color(img, start, ray, y);
		else if (y < window_h)
		{
			if (HAS_ALPHA)
				return ;
			get_floor_color(img, start, ray, y);
		}
		y++;
	}
}

void	walls_draw_vertical_line(t_img *img, t_point start, t_point end,
								t_ray *ray)
{
	int		line_i;
	t_data	*datas;

	datas = data();
	line_i = 0;
	while (line_i < datas->line_w)
	{
		start.x = datas->line_w * ray->index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > datas->window.width - 1)
			start.x = datas->window.width - 1;
		end.x = start.x;
		static_walls_draw_single_vertical_line(img, start, end, ray);
		line_i++;
	}
}
