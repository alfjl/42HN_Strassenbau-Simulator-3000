# include "cub3d.h"

// static t_point	static_get_raypoint()
// {
// 	t_ray	ray;
// 	t_point	p;
// 	float	aTan;
// 	int		depthoffield;
// 	int		map_x;
// 	int		map_y;
// 	int		map_pos;
	
// 	ray.angle = data()->player.angle;
// 	//horizontal
// 	depthoffield = 0;
// 	aTan = -1 / tan(ray.angle);
// 	if (ray.angle > PI) //looking down
// 	{
// 		// ray.y = (((int)data()->player.y>>6)<<6) - 0.0001; //magicnumber
// 		ray.y = ceil(data()->player.y);
// 		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
// 		ray.dy = -64; //magicnumber
// 		ray.dx = -ray.y * aTan;
// 	}
// 	if (ray.angle < PI) //looking up
// 	{
// 		ray.y = trunc(data()->player.y);
// 		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
// 		ray.dy = 64; //magicnumber
// 		ray.dx = -ray.y * aTan;
// 	}
// 	if (ray.angle == 0 || ray.angle == PI)
// 	{
// 		ray.x = data()->player.x;
// 		ray.y = data()->player.y;
// 		depthoffield = 8; //magicnumber
// 	}
// 	while (depthoffield < 8) //magicnumber
// 	{
// 		map_x = (int)(ray.x) >> 6;
// 		map_y = (int)(ray.y) >> 6;
// 		map_pos = map_y * data()->grid.width + map_x;
// 		// if (map_pos < data()->grid.width * data()->grid.height)
// 		ft_printf("map_x: %d, map_y: %d\n", map_x, map_y);
// 		if (map_pos < data()->grid.width * data()->grid.height && data()->map[map_y][map_x] == WALL)
// 			depthoffield = 8; //magicnumber or break?
// 		else
// 		{
// 			ray.x += ray.dx;
// 			ray.y += ray.dy;
// 			depthoffield++;
// 		}
// 	}
// 	p.x = ray.x;
// 	p.y = ray.y;
// 	return (p);
// }

static void	static_display_player()
{
	t_img	img;
	t_point	a;
	t_point	b;

	a.x = data()->player.x * GRID_SIZE;
	a.y = data()->player.y * GRID_SIZE;
	b.x = data()->player.x * GRID_SIZE + data()->player.dx * NOSE;
	b.y = data()->player.y * GRID_SIZE + data()->player.dy * NOSE;

	img.ptr = mlx_new_image(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line_a_to_b(&img, a, b, RED);
	// draw_line_a_to_b(&img, a, static_get_raypoint(), RED);
	
	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[PLAYER_IMG].ptr, a.x - PLAYER_SIZE / 2, a.y - PLAYER_SIZE / 2);
	mlx_destroy_image(data()->mlx, img.ptr);
}

int	minimap(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[MINIMAP_IMG].ptr, 0, 0);
	static_display_player();
	return (EXIT_SUCCESS);
}
