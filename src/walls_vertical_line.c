#include "cub3d.h"

static int	static_get_image(int index)
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

static int	static_determine_tx(int index)
{
	int	tx;

	if (data()->rays[index].orientation == NORTH
		|| data()->rays[index].orientation == SOUTH)
		tx = (data()->rays[index].x - (int)data()->rays[index].x)
			* TEXTURE_SIZE;
	else
		tx = (data()->rays[index].y - (int)data()->rays[index].y)
			* TEXTURE_SIZE;
	if (data()->rays[index].orientation == WEST
		|| data()->rays[index].orientation == SOUTH)
		tx = TEXTURE_SIZE - 1 - tx;
	if (tx < 0) //better check
		tx = 0;
	return (tx);
}

static void	static_copy_color(t_img *img, t_point start, int index, int y)
{
	int		color;
	int		tx;
	float	ty;
	int		image;

	image = static_get_image(index);
	tx = static_determine_tx(index);
	ty = data()->rays[index].tyoffset + (TEXTURE_SIZE
			/ data()->rays[index].line_h) * (y - start.y);
	if (is_inside_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8)))
			+ ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void	static_draw_single_vertical_line(t_img *img, t_point start,
	t_point end, int index)
{
	int		y;

	y = 0;
	if (HAS_ALPHA)
		y = start.y;
	while (y < start.y)
	{
		my_pixel_put(img, start.x, y, data()->map.ceiling.rgb);
		y++;
	}
	while (y <= end.y)
	{
		static_copy_color(img, start, index, y);
		y++;
	}
	if (HAS_ALPHA)
		return ;
	while (y < WINDOW_HEIGHT)
	{
		my_pixel_put(img, start.x, y, data()->map.floor.rgb);
		y++;
	}
}

void	draw_vertical_line(t_img *img, t_point start, t_point end,
	int index)
{
	int		line_i;

	line_i = 0;
	while (line_i < data()->line_w)
	{
		start.x = data()->line_w * index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > data()->window.width - 1)
			start.x = data()->window.width - 1;
		end.x = start.x;
		static_draw_single_vertical_line(img, start, end, index);
		line_i++;
	}	
}
