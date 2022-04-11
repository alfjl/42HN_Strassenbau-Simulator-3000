# include "cub3d.h"

static void	static_draw_vertical_line(t_img *img, t_point start, t_point end, int color)
{
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		my_pixel_put(img, start.x, y, color);
		y++;
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
	if(start.y < 0)
		start.y = 0;
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
			static_draw_vertical_line(&img, start, end, DARK_GREY);
		else if (data()->rays[index].orientation == SOUTH)
			static_draw_vertical_line(&img, start, end, WHITE);
		else if (data()->rays[index].orientation == EAST)
			static_draw_vertical_line(&img, start, end, SILVER);
		else
			static_draw_vertical_line(&img, start, end, GREY);
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