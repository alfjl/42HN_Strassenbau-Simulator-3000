#include "cub3d.h"

static int static_walls_get_texture_image_index(int index)
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

static int static_walls_determine_tx(int index)
{
	int tx;

	if (data()->rays[index].orientation == NORTH || data()->rays[index].orientation == SOUTH)
		tx = (data()->rays[index].x - (int)data()->rays[index].x) * TEXTURE_SIZE;
	else
		tx = (data()->rays[index].y - (int)data()->rays[index].y) * TEXTURE_SIZE;
	if (data()->rays[index].orientation == WEST || data()->rays[index].orientation == SOUTH)
		tx = TEXTURE_SIZE - 1 - tx;
	if (tx < 0)
		tx = 0;
	return (tx);
}

static void static_walls_put_texture_color(t_img *img, t_point start,
										   int index, int y)
{
	int color;
	int tx;
	float ty;
	int image;

	image = static_walls_get_texture_image_index(index);
	tx = static_walls_determine_tx(index);
	ty = data()->rays[index].tyoffset + (TEXTURE_SIZE / data()->rays[index].line_h) * (y - start.y);
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr + (unsigned int)((int)ty * data()->imgs[image].line_len + tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void static_ceiling(t_img *img, t_point start,
							   int index, int y)
{
	int color;
	int tx;
	int ty;
	int image;
	float current_dist;
	float weight;
	float current_floor_x;
	float current_floor_y;

	image = CEILING_IMG;
	current_dist = - data()->window.height / (2.0 * (y - data()->player.dz) - data()->window.height);
	weight = current_dist / data()->rays[index].dist;
	current_floor_x = weight * (data()->rays[index].x - data()->player.x) + data()->player.x / 2;
	current_floor_y = weight * (data()->rays[index].y - data()->player.y) + data()->player.y / 2;
	tx = (current_floor_x - (int)current_floor_x) * TEXTURE_SIZE;
	ty = (current_floor_y - (int)current_floor_y) * TEXTURE_SIZE;
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr + (unsigned int)((int)ty * data()->imgs[image].line_len + tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void static_floor_guide(t_img *img, t_point start,
							   int index, int y)
{
	int color;
	int tx;
	int ty;
	int image;
	float current_dist;
	float weight;
	float current_floor_x;
	float current_floor_y;

	image = FLOOR_IMG;
	current_dist = data()->window.height / (2.0 * (y - data()->player.dz) - data()->window.height);
	weight = current_dist / data()->rays[index].dist;
	current_floor_x = weight * (data()->rays[index].x - data()->player.x) + data()->player.x / 2;
	current_floor_y = weight * (data()->rays[index].y - data()->player.y) + data()->player.y / 2;
	tx = (current_floor_x - (int)current_floor_x) * TEXTURE_SIZE;
	ty = (current_floor_y - (int)current_floor_y) * TEXTURE_SIZE;
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr + (unsigned int)((int)ty * data()->imgs[image].line_len + tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void static_floor_video(t_img *img, t_point start,
							   int index, int y)
{
	(void)img;
	(void)start;
	(void)index;
	(void)y;
	// int		distance = data()->window.width / 2 / tan(ANGLE_OF_VIEW / 2);
	int distance = (data()->window.width / 2) / (tan(ANGLE_OF_VIEW * ONE_DEGREE_IN_RAD / 2));
	printf("d: %d\n", distance);
	// distance = 158;
	int image = FLOOR_IMG;
	int color;
	float tx;
	float ty;
	// while (y < data()->window.height)
	// {
	// float	dy = y - (data()->window.height/ 2.0);
	float dy = y - (data()->rays[index].line_h / 2.0);
	float deg = data()->rays[index].angle;
	float raFix = cos(radian_limits(data()->player.angle - data()->rays[index].angle));
	tx = data()->player.x / 2 + cos(deg) * distance * TEXTURE_SIZE / dy / raFix;
	ty = data()->player.y / 2 - sin(deg) * distance * TEXTURE_SIZE / dy / raFix;
	// 	y++;
	// }
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr + (unsigned int)((int)ty * data()->imgs[image].line_len + tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
	return;
}

static void static_sky(t_img *img, t_point start,
							   int index, int y)
{
	int color;
	int tx;
	int ty;
	int image;

	image = SKY_IMG;
	tx = data()->rays[index].angle * (data()->imgs[image].width / (2 * M_PI));
	ty = y + data()->imgs[image].height / 4 - data()->player.dz;
	if (is_inside_image_limits(tx, ty, &data()->imgs[image]))
	{
		color = *(unsigned int *)(data()->imgs[image].addr + (unsigned int)((int)ty * data()->imgs[image].line_len + tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static void static_walls_draw_single_vertical_line(t_img *img, t_point start,
												   t_point end, int index)
{
	int y;
	t_data *datas;

	datas = data();
	y = 0;
	if (HAS_ALPHA)
		y = start.y;
	while (y < start.y)
	{
		if (SKY_ENABLED)
			static_sky(img, start, index, y);
		else
			my_pixel_put(img, start.x, y, datas->map.ceiling.rgb);
		if (CEILING_TEXTURE_ENABLED)
			static_ceiling(img, start, index, y);
		y++;
	}
	while (y < end.y)
	{
		static_walls_put_texture_color(img, start, index, y);
		y++;
	}
	if (HAS_ALPHA)
		return;
	while (y < datas->window.height)
	{

		if (FLOOR_TEXTURE_ENABLED && !FLOOR_TEXTURE_VERTICAL)
			return;
		else if (FLOOR_TEXTURE_ENABLED && FLOOR_TEXTURE_VERTICAL == GUIDE)
			static_floor_guide(img, start, index, y);
		else if (FLOOR_TEXTURE_ENABLED && FLOOR_TEXTURE_VERTICAL == VIDEO)
			static_floor_video(img, start, index, y);
		else
			my_pixel_put(img, start.x, y, datas->map.floor.rgb);
		y++;
	}
}

void walls_draw_vertical_line(t_img *img, t_point start, t_point end,
							  int index)
{
	int line_i;
	t_data *datas;

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
