# include "cub3d.h"
/*
static void	static_display_ray()
{
	t_ray	ray;
	t_point	p;
	float	aTan;
	int		depthoffield;
	
	ray.angle = data()->player.angle;
	//horizontal
	depthoffield = 0;
	aTan = -1 / tan(ray.angle);
	if (ray.angle > PI) //looking up
	{
		ray.y = trunc(data()->player.y);
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = -1;
		ray.dx = -ray.y * aTan;
	}
	if (ray.angle < PI) //looking down
	{
		ray.y = ceil(data()->player.y);
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = 1;
		ray.dx = -ray.y * aTan;
	}
	if (ray.angle == 0 || ray.angle == PI)
	{
		ray.x = data()->player.x;
		ray.y = data()->player.y;
		depthoffield = 8; //magicnumber
	}
	while (depthoffield < 8) //magicnumber
	{
		// map_x = ray.x;
		// map_y = ray.y;
		// map_pos = map_y * data()->grid.width + map_x;
		// if (map_pos < data()->grid.width * data()->grid.height)
		ft_printf("r_x: %d, r_y: %d\n", ray.x, ray.y);
		if (ray.y >= 0 && ray.x >= 0 && ray.y < data()->grid.height && ray.x < data()->grid.width && data()->map[(int)ray.y][(int)ray.x] == WALL)
			depthoffield = 8; //magicnumber or break?
		else
		{
			ray.x += ray.dx;
			ray.y += ray.dy;
			depthoffield++;
		}
	}
	if (ray.y >= 0 && ray.x >= 0 && ray.y < data()->grid.height && ray.x < data()->grid.width)
	{
		p.x = ray.x * GRID_SIZE;
		p.y = ray.y * GRID_SIZE;
		ft_printf("p_x: %d, p_y: %d\n", p.x, p.y);
		t_img	img;
		t_point	a;
		// t_point	b;

		a.x = data()->player.x * GRID_SIZE;
		a.y = data()->player.y * GRID_SIZE;
		// b.x = data()->player.x * GRID_SIZE + data()->player.dx * NOSE;
		// b.y = data()->player.y * GRID_SIZE + data()->player.dy * NOSE;
		img.ptr = mlx_new_image(data()->mlx, data()->window.width, data()->window.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
		draw_line_a_to_b(&img, a, p, RED);
		mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
		mlx_destroy_image(data()->mlx, img.ptr);
	}
}
*/
static void	static_display_player()
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[PLAYER_IMG].ptr, data()->player.x * GRID_SIZE - PLAYER_SIZE / 2, data()->player.y * GRID_SIZE - PLAYER_SIZE / 2);
}

int	minimap(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[MINIMAP_IMG].ptr, 0, 0);
	static_display_player();
	// static_display_ray();
	return (EXIT_SUCCESS);
}
