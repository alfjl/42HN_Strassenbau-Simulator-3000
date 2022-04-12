# include "cub3d.h"

static void	static_update_pos(t_keys *keys)
{
	if (keys->forwards)
	{
		data()->player.x += data()->player.dx;
		data()->player.y += data()->player.dy;
	}
	if (keys->turnleft)
	{
		data()->player.angle -= STEP_A;
		if (data()->player.angle < 0)
			data()->player.angle += 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
	if (keys->turnright)
	{
		data()->player.x -= data()->player.dx;
		data()->player.y -= data()->player.dy;
	}
	if (keys->backwards)
	{
		data()->player.angle += STEP_A;
		if (data()->player.angle > 2 * PI)
			data()->player.angle -= 2 * PI;
		data()->player.dx = cos(data()->player.angle) * STEP;
		data()->player.dy = sin(data()->player.angle) * STEP;
	}
}

// void	static_test2(void)
// {
// 	int	x;
// 	int	y;
// 	int	tx;
// 	int	ty;
// 	float	ty_step;
// 	int	color;
// 	t_img	img;

// 	img.ptr = mlx_new_image(data()->mlx, TEXTURE_SIZE, TEXTURE_SIZE);
// 	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

// 	float lineH = TEXTURE_SIZE;
// 	ty_step = lineH / TEXTURE_SIZE;
// 	x = 0;
// 	while (x < TEXTURE_SIZE)
// 	{
// 		tx = x % TEXTURE_SIZE;
// 		// printf("tx: %d\n", tx);
// 		y = 0;
// 		ty = y;
// 		while (y < TEXTURE_SIZE)
// 		{
// 			color = *(unsigned int *)(data()->imgs[SOUTH_IMG].addr
// 					+ (unsigned int)(ty * data()->imgs[SOUTH_IMG].line_length
// 						+ tx * (data()->imgs[SOUTH_IMG].bits_per_pixel / 8)));
// 			my_pixel_put(&img, x, y, color);
// 			y++;
// 			ty += ty_step;
// 		}
// 		x++;
// 	}

// 	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, GRID_SIZE, 0);
// 	mlx_destroy_image(data()->mlx, img.ptr);
// }

// void	static_test(void)
// {
// 	int	x;
// 	int	y;
// 	int	color;
// 	int	scale;
// 	t_img	img;

// 	scale = TEXTURE_SIZE / GRID_SIZE;
// 	// img.ptr = mlx_xpm_file_to_image(data()->mlx, "./textures/bricks.xpm", &img.width, &img.height);
// 	img.ptr = mlx_new_image(data()->mlx, TEXTURE_SIZE / scale, TEXTURE_SIZE / scale);
// 	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

// 	y = 0;
// 	while (y < TEXTURE_SIZE / scale)
// 	{
// 		x = 0;
// 		while (x < TEXTURE_SIZE / scale)
// 		{
// 			color = *(unsigned int *)(data()->imgs[SOUTH_IMG].addr
// 					+ (unsigned int)(y * data()->imgs[SOUTH_IMG].line_length * scale
// 						+ x * scale * (data()->imgs[SOUTH_IMG].bits_per_pixel / 8)));
// 			my_pixel_put(&img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}

// 	// mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[SOUTH_IMG].ptr, 0, 0);
// 	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
// 	mlx_destroy_image(data()->mlx, img.ptr);
// }

int	game(t_keys *keys)
{
	// if (data()->frame != 0)
	// {
	// 	data()->frame++;
	// 	if (data()->frame == 60)
	// 		data()->frame = 0;
	// 	return (EXIT_SUCCESS);
	// }
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[BACKGROUND_IMG].ptr, 0, 0);
	static_update_pos(keys);
	walls_display();
	minimap_display();
	// static_test();
	// static_test2();
	// data()->frame++;
	mlx_string_put(data()->mlx, data()->win, 20, 500, ORANGE, get_fps());
	mlx_string_put(data()->mlx, data()->win, 40, 500, ORANGE, "FPS");
	return (EXIT_SUCCESS);
}
