# include "cub3d.h"

// void	player()
// {
	
// }

static void	static_paint_cell(t_img *img, int img_y, int img_x)
{
	int		x;
	int		y;

	y = 1;
	while (y < GRID_SIZE - 1)
	{
		x = 1;
		while (x < GRID_SIZE - 1)
		{
			if (data()->map[img_y][img_x] == '1')
				my_pixel_put(img, img_x * GRID_SIZE + x, img_y * GRID_SIZE + y, GREY);
			else
				my_pixel_put(img, img_x * GRID_SIZE + x, img_y * GRID_SIZE + y, WHITE);
			x++;
		}
		y++;
	}
}

void	minimap(void)
{
	t_img	img;
	int		x;
	int		y;

	img.ptr = mlx_new_image(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	y = 0;
	while (data()->map[y] != NULL)
	{
		x = 0;
		while (data()->map[y][x] != '\0')
		{
			static_paint_cell(&img, y, x);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
	// mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[MINIMAP_IMG].ptr, 0, 0);
	// mlx_destroy_image(data()->mlx, img.ptr);
}
