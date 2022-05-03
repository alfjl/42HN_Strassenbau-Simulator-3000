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

static int	static_get_walls_color(t_img *img, t_ray *ray, int y)
{
	int		color;
	int		tx;
	float	ty;
	int		image;

	color = GREEN;
	image = static_walls_get_texture_image_index(ray->index);
	tx = static_walls_determine_tx(ray->index);
	ty = ray->tyoffset
		+ (TEXTURE_SIZE / ray->line_h) * (y - ray->start_y);
	// if (ty < 0)
	// 	ty = 0;
	if (ty > data()->window.height - 1)
		ty = data()->window.height - 1;
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		// my_pixel_put(img, ray->screen_x, y, color);
	}
	if (color == GREEN)
		printf("tx: %d, ty: %f\n", tx, ty);
	return (color);
}

static void	static_walls_draw_single_vertical_line(t_data *data, t_img *img, t_ray *ray)
{
	int		y;
	int		window_h;
	int		color;

	window_h = data->window.height;
	y = 0;
	if (HAS_ALPHA)
		y = ray->start_y;
	while (y < window_h)
	{
		if (y < ray->start_y)
			color = get_ceiling_color(img, ray, y);
		else if (y <= ray->end_y)
		{
			if (ray->is_infinite)
				color = get_ceiling_color(img, ray, y);
			else
				color = static_get_walls_color(img, ray, y);
		}
		else if (y < window_h)
		{
			if (HAS_ALPHA)
				return ;
			color = get_floor_color(img, ray, y);
		}
		my_pixel_put(img, ray->screen_x, y, color);
		y++;
	}
}

void	walls_draw_vertical_line(t_data *data, t_img *img, t_ray *ray)
{
	int		line_i;

	line_i = 0;
	while (line_i < data->line_w)
	{
		ray->screen_x = data->line_w * ray->index + line_i;
		if (ray->screen_x < 0)
			ray->screen_x = 0;
		if (ray->screen_x > data->window.width - 1)
			ray->screen_x = data->window.width - 1;
		static_walls_draw_single_vertical_line(data, img, ray);
		line_i++;
	}
}
