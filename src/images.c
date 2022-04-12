# include "cub3d.h"

static void static_create_3Dbackground()
{
	int		x;
	int		y;

	data()->imgs[BACKGROUND_IMG].ptr = mlx_new_image(data()->mlx, data()->window.width, data()->window.height);
	data()->imgs[BACKGROUND_IMG].addr = mlx_get_data_addr(data()->imgs[BACKGROUND_IMG].ptr, &data()->imgs[BACKGROUND_IMG].bits_per_pixel, &data()->imgs[BACKGROUND_IMG].line_length, &data()->imgs[BACKGROUND_IMG].endian);
	
	y = 0;
	while (y < data()->window.height)
	{
		x = 0;
		while (x < data()->window.width)
		{
			if (y < data()->window.height / 2)
				my_pixel_put(&data()->imgs[BACKGROUND_IMG], x, y, data()->map.ceiling.rgb);
			else
				my_pixel_put(&data()->imgs[BACKGROUND_IMG], x, y, data()->map.floor.rgb);
			x++;
		}
		y++;
	}
	data()->imgs[BACKGROUND_IMG].width = data()->window.width;
	data()->imgs[BACKGROUND_IMG].height = data()->window.height;
}

static void static_create_player_img()
{
	int	x;
	int y;
	data()->imgs[PLAYER_IMG].ptr = mlx_new_image(data()->mlx, PLAYER_SIZE, PLAYER_SIZE);
	data()->imgs[PLAYER_IMG].addr = mlx_get_data_addr(data()->imgs[PLAYER_IMG].ptr, &data()->imgs[PLAYER_IMG].bits_per_pixel, &data()->imgs[PLAYER_IMG].line_length, &data()->imgs[PLAYER_IMG].endian);
	
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			my_pixel_put(&data()->imgs[PLAYER_IMG], x, y, BLACK);
			x++;
		}
		y++;
	}
	data()->imgs[PLAYER_IMG].width = PLAYER_SIZE;
	data()->imgs[PLAYER_IMG].height = PLAYER_SIZE;
}

static void	static_paint_borders(t_img *img, int img_y, int img_x)
{
	int		x;
	int		y;

	y = 0;
	while (y < GRID_SIZE)
	{
		x = 0;
		while (x < GRID_SIZE)
		{
			if ((y == 0 || y == GRID_SIZE - 1) || (x == 0 || x == GRID_SIZE -1))
				my_pixel_put(img, img_x * GRID_SIZE + x, img_y * GRID_SIZE + y, BLACK);
			x++;
		}
		y++;
	}
}

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
			if (data()->map.grid[img_y][img_x] == WALL)
				my_pixel_put(img, img_x * GRID_SIZE + x, img_y * GRID_SIZE + y, GREY);
			else
				my_pixel_put(img, img_x * GRID_SIZE + x, img_y * GRID_SIZE + y, WHITE);
			x++;
		}
		y++;
	}
	static_paint_borders(img, img_y, img_x);
}

static void static_create_minimap_img()
{
	int		x;
	int		y;

	data()->imgs[MINIMAP_IMG].ptr = mlx_new_image(data()->mlx, data()->minimap.width, data()->minimap.height);
	data()->imgs[MINIMAP_IMG].addr = mlx_get_data_addr(data()->imgs[MINIMAP_IMG].ptr, &data()->imgs[MINIMAP_IMG].bits_per_pixel, &data()->imgs[MINIMAP_IMG].line_length, &data()->imgs[MINIMAP_IMG].endian);
	
	y = 0;
	while (data()->map.grid[y] != NULL)
	{
		x = 0;
		while (data()->map.grid[y][x] != '\0')
		{
			static_paint_cell(&data()->imgs[MINIMAP_IMG], y, x);
			x++;
		}
		y++;
	}
	data()->imgs[MINIMAP_IMG].width = data()->minimap.width;
	data()->imgs[MINIMAP_IMG].height = data()->minimap.height;
}

static void	static_create_empty_img(int image)
{
	data()->imgs[image].ptr = mlx_xpm_file_to_image(data()->mlx, data()->imgs[image].path, &data()->imgs[image].width, &data()->imgs[image].height);
	data()->imgs[image].addr = mlx_get_data_addr(data()->imgs[image].ptr, &data()->imgs[image].bits_per_pixel, &data()->imgs[image].line_length, &data()->imgs[image].endian);
}

void	create_images(void)
{
	static_create_minimap_img();
	static_create_3Dbackground();
	static_create_player_img();
	static_create_empty_img(SOUTH_IMG);
	static_create_empty_img(NORTH_IMG);
	static_create_empty_img(EAST_IMG);
	static_create_empty_img(WEST_IMG);
}