# include "cub3d.h"

void	draw_3Dwallsegment(t_ray ray, int index)
{
	float	lineH;
	t_point	start;
	t_point end;
	t_img	img;

	img.ptr = mlx_new_image_alpha(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	lineH = (data()->window.height / ray.dist);
	start.y = -lineH / 2 + data()->window.height / 2;
	if(start.y < 0)
		start.y = 0;
	end.y = lineH / 2 + data()->window.height / 2;
	if(end.y >= data()->window.height)
		end.y = data()->window.height - 1;
	
	int offset;
	offset = - data()->window.width / NUMBER_OF_RAYS / 2;
	while (offset <= data()->window.width / NUMBER_OF_RAYS / 2)
	{
		start.x = data()->window.width / NUMBER_OF_RAYS * index + offset;
		if (start.x < 0)
			start.x = 0;
		if (start.x > data()->window.width)
			start.x = data()->window.width;
		end.x = start.x;
		if (ray.orientation == HORIZONTAL)
			draw_line_a_to_b(&img, start, end, GREY);
		else
			draw_line_a_to_b(&img, start, end, WHITE);
		offset++;
	}

	mlx_put_image_to_window(data()->mlx, data()->win3D, img.ptr, 0, 0);
	mlx_destroy_image(data()->mlx, img.ptr);
}

int	game(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win3D, data()->imgs[BACKGROUND_IMG].ptr, 0, 0);
	// static_display_rays();
	// static_display_player();
	return (EXIT_SUCCESS);
}