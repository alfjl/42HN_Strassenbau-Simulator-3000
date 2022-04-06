# include "cub3d.h"

static t_ray	static_calculate_ray_v(float angle)
{
	t_ray	ray;
	float	nTan;
	int		depthoffield;
	
	ray.angle = angle;
	//vertical
	depthoffield = 0;
	nTan = -tan(ray.angle);
	if (ray.angle > PI1 && ray.angle < PI3) //looking left
	{
		ray.x = (float)trunc(data()->player.x) - EDGE;
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = -1;
		ray.dy = -ray.dx * nTan;
	}
	if (ray.angle < PI1 || ray.angle > PI3) //looking right
	{
		ray.x = (float)ceil(data()->player.x);
		ray.y = (data()->player.x - ray.x) * nTan + data()->player.y;
		ray.dx = 1;
		ray.dy = -ray.dx * nTan;
	}
	if (ray.angle == 0 || ray.angle == PI)
	{
		ray.x = data()->player.x;
		ray.y = data()->player.y;
		depthoffield = 8; //magicnumber
	}
	while (depthoffield < 8) //magicnumber
	{
		// ft_printf("r_x: %d, r_y: %d\n", ray.x, ray.y);
		if (ray.y >= 0 && ray.x >= 0 && ray.y < data()->grid.height && ray.x < data()->grid.width && data()->map[(int)ray.y][(int)ray.x] == WALL)
			depthoffield = 8; //magicnumber or break?
		else
		{
			ray.x += ray.dx;
			ray.y += ray.dy;
			depthoffield++;
		}
	}
	ray.orientation = VERTICAL;
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x) + (ray.y - data()->player.y) * (ray.y - data()->player.y));
	ray.dist = ray.len;
	return (ray);
}

static t_ray	static_calcualte_ray_h(float angle)
{
	t_ray	ray;
	float	aTan;
	int		depthoffield;
	
	ray.angle = angle;
	//horizontal
	depthoffield = 0;
	aTan = -1 / tan(ray.angle);
	if (ray.angle > PI) //looking up
	{
		ray.y = (float)trunc(data()->player.y) - EDGE;
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = -1;
		ray.dx = -ray.dy * aTan;
	}
	if (ray.angle < PI) //looking down
	{
		ray.y = (float)ceil(data()->player.y);
		ray.x = (data()->player.y - ray.y) * aTan + data()->player.x;
		ray.dy = 1;
		ray.dx = -ray.dy * aTan;
	}
	if (ray.angle == 0 || ray.angle == PI)
	{
		ray.x = data()->player.x;
		ray.y = data()->player.y;
		depthoffield = 8; //magicnumber
	}
	while (depthoffield < 8) //magicnumber
	{
		// ft_printf("r_x: %d, r_y: %d\n", ray.x, ray.y);
		if (ray.y >= 0 && ray.x >= 0 && ray.y < data()->grid.height && ray.x < data()->grid.width && data()->map[(int)ray.y][(int)ray.x] == WALL)
			depthoffield = 8; //magicnumber or break?
		else
		{
			ray.x += ray.dx;
			ray.y += ray.dy;
			depthoffield++;
		}
	}
	ray.orientation = HORIZONTAL;
	ray.len = sqrt((ray.x - data()->player.x) * (ray.x - data()->player.x) + (ray.y - data()->player.y) * (ray.y - data()->player.y));
	ray.dist = ray.len;
	return (ray);
}

static t_ray	static_draw_ray(float angle)
{
	
	t_ray	rays[2];
	t_ray	ray;
	t_point	p;

	rays[0] = static_calcualte_ray_h(angle);
	rays[1] = static_calculate_ray_v(angle);
	printf("h: %f, v: %f\n", rays[0].len, rays[1].len); //remove
	if (rays[0].len < rays[1].len)
		ray = rays[0];
	else
		ray = rays[1];
	printf("r_a: %f, p_a: %f, r_x: %f, r_y: %f, r_dx: %f, p_dx: %f, r_dy: %f, p_dy: %f\n", ray.angle, data()->player.angle, ray.x, ray.y, ray.dx, data()->player.dx, ray.dy, data()->player.dy);
	if (ray.y >= 0 && ray.x >= 0 && ray.y < data()->grid.height && ray.x < data()->grid.width)
	{
		p.x = ray.x * GRID_SIZE;
		p.y = ray.y * GRID_SIZE;
		t_img	img;
		t_point	a;

		a.x = data()->player.x * GRID_SIZE;
		a.y = data()->player.y * GRID_SIZE;
		img.ptr = mlx_new_image_alpha(data()->mlx, data()->window.width, data()->window.height);
		img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
		draw_line_a_to_b(&img, a, p, RED);
		mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
		mlx_destroy_image(data()->mlx, img.ptr);
	}
	return (ray);
}

static void	static_display_rays()
{
	int		i;
	float	angle;
	
	i = 0;
	angle = data()->player.angle - NUMBER_OF_RAYS / 2 * DR;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	while (i < NUMBER_OF_RAYS)
	{
		draw_3Dwallsegment(static_draw_ray(angle), i);
		angle += DR;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		i++;
	}
}

static void	static_display_player()
{
	t_img	img;
	t_point	a;
	t_point	b;

	a.x = data()->player.x * GRID_SIZE;
	a.y = data()->player.y * GRID_SIZE;
	b.x = data()->player.x * GRID_SIZE + data()->player.dx * NOSE;
	b.y = data()->player.y * GRID_SIZE + data()->player.dy * NOSE;
	img.ptr = mlx_new_image_alpha(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line_a_to_b(&img, a, b, BLACK);
	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
	mlx_destroy_image(data()->mlx, img.ptr);
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[PLAYER_IMG].ptr, data()->player.x * GRID_SIZE - PLAYER_SIZE / 2, data()->player.y * GRID_SIZE - PLAYER_SIZE / 2);
}

int	minimap(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[MINIMAP_IMG].ptr, 0, 0);
	game();
	static_display_rays();
	static_display_player();
	return (EXIT_SUCCESS);
}
