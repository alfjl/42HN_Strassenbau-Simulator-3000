# include "cub3d.h"

static t_ray	static_ray_calculate(float angle, int index)
{
	
	t_ray	rays[2];
	t_ray	ray;
	// t_point	p;
	// t_point	a;

	rays[0] = ray_calculate_horizontal(angle, index);
	rays[1] = ray_calculate_vertical(angle, index);
	if (rays[0].len < rays[1].len)
		ray = rays[0];
	else
		ray = rays[1];
	return (ray);
}

void	rays_draw_to_image(void)
{
	int		i;
	t_data	*datas;
	t_img	*img;
	t_point	p;
	t_point	a;

	datas = data();
	img = &datas->imgs[RAYS_IMG];
	img->ptr = mlx_new_image_alpha(datas->mlx, datas->minimap.width, datas->minimap.height);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
		{
			if (datas->rays[i].y >= 0 && datas->rays[i].x >= 0 && datas->rays[i].y < data()->map.height && datas->rays[i].x < data()->map.width)
			{
				p.x = datas->rays[i].x * GRID_SIZE;
				p.y = datas->rays[i].y * GRID_SIZE;
				a.x = data()->player.x * GRID_SIZE;
				a.y = data()->player.y * GRID_SIZE;
				draw_line_a_to_b(img, a, p, RED);
			}
		}
		i++;
	}
}

void	rays_calculate(void)
{
	int		i;
	float	angle;
	t_data	*datas;

	datas = data();
	i = 0;
	angle = datas->player.angle - ANGLE_OF_VIEW / 2 * DR;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	while (i < NUMBER_OF_RAYS)
	{
		datas->rays[i] = static_ray_calculate(angle, i);
		datas->rays[i].lineH = (datas->window.height / datas->rays[i].dist) * datas->window.width / datas->window.height * 60 / ANGLE_OF_VIEW;
		angle += ANGLE_OF_VIEW * DR / NUMBER_OF_RAYS;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		i++;
	}
}