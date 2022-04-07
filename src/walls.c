# include "cub3d.h"

static float	static_calculate_dlineH(int ray_index, int lineW)
{
	float	lineH;

	if (ray_index == NUMBER_OF_RAYS - 1)
		return (0);

	lineH = (data()->rays[ray_index + 1].lineH - data()->rays[ray_index].lineH) / lineW;
	return (0);
	return (lineH);
}

static void	static_draw_3Dwallsegment(int index)
{
	t_point	start;
	t_point end;
	t_img	img;
	int		lineW;
	float	lineH;
	float	dlineH;

	img.ptr = mlx_new_image_alpha(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	lineW = data()->window.width / (NUMBER_OF_RAYS - 1);
	dlineH = static_calculate_dlineH(index, lineW);
 	int line_i;
	line_i = 0;
	while (line_i < lineW)
	{
		lineH = data()->rays[index].lineH + line_i * dlineH;
		start.y = -lineH / 2 + data()->window.height / 2;
		if(start.y < 0)
			start.y = 0;
		end.y = lineH / 2 + data()->window.height / 2;
		if(end.y >= data()->window.height)
			end.y = data()->window.height - 1;
		
		
		
		
		start.x = lineW * index + line_i;
		if (start.x < 0)
			start.x = 0;
		if (start.x > data()->window.width - 1)
			start.x = data()->window.width - 1;
		end.x = start.x;
		if (data()->rays[index].orientation == HORIZONTAL)
			draw_line_a_to_b(&img, start, end, GREY);
		else
			draw_line_a_to_b(&img, start, end, WHITE);
		line_i++;
	}
	// start.x = data()->window.width - 1;
	// end.x = start.x;
	// draw_line_a_to_b(&img, start, end, RED);
	// start.x = 0;
	// end.x = start.x;
	// draw_line_a_to_b(&img, start, end, BLUE);
	mlx_put_image_to_window(data()->mlx, data()->win3D, img.ptr, 0, 0);
	mlx_destroy_image(data()->mlx, img.ptr);
}

void	display_3Dwalls(void)
{
	int i;

	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_draw_3Dwallsegment(i);
		i++;
	}
}