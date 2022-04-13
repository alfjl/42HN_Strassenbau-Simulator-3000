#include "cub3d.h"

static void	static_draw_vertical_line(t_img *img, t_point start, t_point end, int image, int index)
{
	int		y;
	int		tx;
	float	ty;
	float	ty_step;
	int		color;

	if (data()->rays[index].orientation == NORTH
		|| data()->rays[index].orientation == SOUTH)
		tx = (data()->rays[index].x - (int)data()->rays[index].x)
			* TEXTURE_SIZE;
	else
		tx = (data()->rays[index].y - (int)data()->rays[index].y)
			* TEXTURE_SIZE;
	if (tx < 0) //better check
		tx = 0;
	ty = data()->rays[index].tyoffset;
	ty_step = TEXTURE_SIZE / data()->rays[index].line_h;
	y = start.y;
	while (y <= end.y)
	{
		color = *(unsigned int *)(data()->imgs[image].addr
			+ (unsigned int)((int)ty * data()->imgs[image].line_length
				+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
		y++;
		ty += ty_step;
	}
}

static void	static_draw_wallsegment(int index, t_img *img)
{
	t_point	start;
	t_point	end;
	float	line_h;
	int		line_i;

	line_h = data()->rays[index].line_h;
	start.y = -line_h / 2 + data()->window.height / 2;
	data()->rays[index].tyoffset = 0;
	if (start.y < 0)
	{
		data()->rays[index].tyoffset = fabs((float)start.y)
		/ line_h * TEXTURE_SIZE;
		start.y = 0;
	}
	end.y = line_h / 2 + data()->window.height / 2;
	if (end.y >= data()->window.height)
		end.y = data()->window.height - 1;
	line_i = 0;
	while (line_i < data()->line_w)
	{
		start.x = data()->line_w * index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > data()->window.width - 1)
			start.x = data()->window.width - 1;
		end.x = start.x;
		if (data()->rays[index].orientation == NORTH)
			static_draw_vertical_line(img, start, end, NORTH_IMG, index);
		else if (data()->rays[index].orientation == SOUTH)
			static_draw_vertical_line(img, start, end, SOUTH_IMG, index);
		else if (data()->rays[index].orientation == EAST)
			static_draw_vertical_line(img, start, end, EAST_IMG, index);
		else
			static_draw_vertical_line(img, start, end, WEST_IMG, index);
		line_i++;
	}
}

void	walls_draw_to_image(void)
{
	int		i;
	t_img	*img;

	img = &data()->imgs[WALLS_IMG];
	img->ptr = mlx_new_image_alpha(data()->mlx, data()->window.width,
			data()->window.height);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_draw_wallsegment(i, img);
		i++;
	}
}
