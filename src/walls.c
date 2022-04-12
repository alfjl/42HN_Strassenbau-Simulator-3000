# include "cub3d.h"

static void	static_draw_vertical_line(t_img *img, t_point start, t_point end, int image, int index)
{
	int		y;
	int		tx;
	float	ty;
	float	ty_step;
	int		color;
	// float	ty; ///texture_y
	// float	c;

	if (data()->rays[index].orientation == NORTH || data()->rays[index].orientation == SOUTH)
		tx = (data()->rays[index].x - (int)data()->rays[index].x) * TEXTURE_SIZE;
	else
		tx = (data()->rays[index].y - (int)data()->rays[index].y) * TEXTURE_SIZE;
	ty =  data()->rays[index].tyoffset;
	ty_step = TEXTURE_SIZE / data()->rays[index].lineH;
	y = start.y;
	while (y <= end.y)
	{
		// printf("x: %d, y: %d, tx: %d, ty: %f, ty_s: %f\n", start.x, y, tx, ty, ty_step);
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_length
					+ tx * (data()->imgs[image].bits_per_pixel / 8)));
		my_pixel_put(img, start.x, y, color);
		y++;
		ty += ty_step;
	}
}

static void	static_draw_3Dwallsegment(int index)
{
	t_point	start;
	t_point end;
	t_img	img;
	int		lineW;
	float	lineH;

	img.ptr = mlx_new_image_alpha(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	lineW = data()->window.width / (NUMBER_OF_RAYS - 1);


	lineH = data()->rays[index].lineH;
	start.y = -lineH / 2 + data()->window.height / 2;
	data()->rays[index].tyoffset = 0;
	if(start.y < 0)
	{
		data()->rays[index].tyoffset = fabs((float)start.y) / lineH * TEXTURE_SIZE;
		start.y = 0;
	}
	end.y = lineH / 2 + data()->window.height / 2;
	if(end.y >= data()->window.height)
		end.y = data()->window.height - 1;

 	int line_i;
	line_i = 0;
	while (line_i < lineW)
	{
		start.x = lineW * index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > data()->window.width - 1)
			start.x = data()->window.width - 1;
		end.x = start.x;
		if (data()->rays[index].orientation == NORTH)
			static_draw_vertical_line(&img, start, end, NORTH_IMG, index);
		else if (data()->rays[index].orientation == SOUTH)
			static_draw_vertical_line(&img, start, end, SOUTH_IMG, index);
		else if (data()->rays[index].orientation == EAST)
			static_draw_vertical_line(&img, start, end, EAST_IMG, index);
		else
			static_draw_vertical_line(&img, start, end, WEST_IMG, index);
		line_i++;
	}
	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
	mlx_destroy_image(data()->mlx, img.ptr);
}

void	walls_display(void)
{
	int i;

	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_draw_3Dwallsegment(i);
		i++;
	}
}