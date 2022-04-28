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
	if (tx < 0)
		tx = 0;
	return (tx);
}

static void	static_walls_put_texture_color(t_img *img, t_point start,
	int index, int y)
{
	int		color;
	int		tx;
	float	ty;
	int		image;

	image = static_walls_get_texture_image_index(index);
	tx = static_walls_determine_tx(index);
	ty = data()->rays[index].tyoffset + (TEXTURE_SIZE
			/ data()->rays[index].line_h) * (y - start.y);
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void	static_floor(t_img *img, t_point start,
	int index, int y)
{
	int		color;
	int		tx;
	float	ty;
	int		image;
	float	current_dist;
	float	weight;
	float	current_floor_x;
	float	current_floor_y;

	(void)current_dist;
	(void)weight;
	(void)current_floor_x;
	(void)current_floor_y;
	image = FLOOR_IMG;
	current_dist = data()->window.height / (2.0 * y - data()->window.height);
	weight = current_dist / data()->rays[index].dist;
	current_floor_x = weight * data()->rays[index].x + (1.0 - weight) * data()->player.x;
	current_floor_y = weight * data()->rays[index].y + (1.0 - weight) * data()->player.y;
	// tx = (int)(current_floor_x * TEXTURE_SIZE) % TEXTURE_SIZE;
	// ty = (int)(current_floor_y * TEXTURE_SIZE) % TEXTURE_SIZE;
	tx = (current_floor_x - (int)current_floor_x) * TEXTURE_SIZE;
	ty = (current_floor_y - (int)current_floor_y) * TEXTURE_SIZE;
	// tx = data()->player.x / 2 + cos(data()->rays[index].angle) * 158 * TEXTURE_SIZE / (y - (data()->window.height / 2.0)) / cos(radian_limits(data()->player.angle - data()->rays[index].angle));
	// ty = data()->player.x / 2 - sin(data()->rays[index].angle) * 158 * TEXTURE_SIZE / (y - (data()->window.height / 2.0)) / cos(radian_limits(data()->player.angle - data()->rays[index].angle));
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void	static_walls_draw_single_vertical_line(t_img *img, t_point start,
	t_point end, int index)
{
	int		y;
	t_data	*datas;

	datas = data();
	y = 0;
	if (HAS_ALPHA)
		y = start.y;
	while (y < start.y)
	{
		my_pixel_put(img, start.x, y, datas->map.ceiling.rgb);
		y++;
	}
	while (y < end.y)
	{
		static_walls_put_texture_color(img, start, index, y);
		y++;
	}
	if (HAS_ALPHA)
		return ;
	while (y < datas->window.height)
	{
		
		if (FLOOR_TEXTURE_ENABLED && FLOOR_TEXTURE_HORIZONTAL)
			return ;
		else if (FLOOR_TEXTURE_ENABLED)
			static_floor(img, start, index, y);
		else
			my_pixel_put(img, start.x, y, datas->map.floor.rgb);
		y++;
	}
}

void	walls_draw_vertical_line(t_img *img, t_point start, t_point end,
	int index)
{
	int		line_i;
	t_data	*datas;

	datas = data();
	line_i = 0;
	while (line_i < datas->line_w)
	{
		start.x = datas->line_w * index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > datas->window.width - 1)
			start.x = datas->window.width - 1;
		end.x = start.x;
		static_walls_draw_single_vertical_line(img, start, end, index);
		line_i++;
	}	
}
