#include "cub3d.h"

static void	static_create_background(void)
{
	int		x;
	int		y;
	t_img	*img;

	img = &data()->imgs[BACKGROUND_IMG];
	img->ptr = my_new_image(data()->mlx, data()->window.width, data()->window.height, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	y = 0;
	while (y < data()->window.height)
	{
		x = 0;
		while (x < data()->window.width)
		{
			if (y < data()->window.height / 2)
				my_pixel_put(img, x, y, data()->map.ceiling.rgb);
			else
				my_pixel_put(img, x, y, data()->map.floor.rgb);
			x++;
		}
		y++;
	}
}

static void	static_create_player_img(void)
{
	int		x;
	int		y;
	t_img	*img;

	img = &data()->imgs[PLAYER_IMG];
	img->ptr = my_new_image(data()->mlx, PLAYER_SIZE, PLAYER_SIZE, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			my_pixel_put(img, x, y, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
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
				my_pixel_put(img, img_x * GRID_SIZE + x,
					img_y * GRID_SIZE + y, MINIMAP_GRID_COLOR);
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
				my_pixel_put(img, img_x * GRID_SIZE + x,
					img_y * GRID_SIZE + y, MINIMAP_WALL_COLOR);
			else
				my_pixel_put(img, img_x * GRID_SIZE + x,
					img_y * GRID_SIZE + y, MINIMAP_SPACE_COLOR);
			x++;
		}
		y++;
	}
	static_paint_borders(img, img_y, img_x);
}

static void	static_create_minimap_img(void)
{
	int		x;
	int		y;
	t_img	*img;

	img = &data()->imgs[MINIMAP_IMG];
	img->ptr = my_new_image(data()->mlx, data()->minimap.width, data()->minimap.height, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	y = 0;
	while (data()->map.grid[y] != NULL)
	{
		x = 0;
		while (data()->map.grid[y][x] != '\0')
		{
			static_paint_cell(img, y, x);
			x++;
		}
		y++;
	}
}

void	images_create(void)
{
	static_create_minimap_img();
	static_create_background();
	static_create_player_img();
}
