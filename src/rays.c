#include "cub3d.h"

static t_ray	static_ray_get(float angle)
{
	t_ray	ray_horizontal;
	t_ray	ray_vertival;

	ray_horizontal = ray_calculate_horizontal(angle);
	ray_vertival = ray_calculate_vertical(angle);
	if (ray_horizontal.len < ray_vertival.len)
		return (ray_horizontal);
	else
		return (ray_vertival);
}

static void	static_draw_single_ray(t_img *img, t_point player, t_point ray,
	int i)
{
	t_ray	*rays;

	rays = data()->rays;
	if (rays[i].y >= 0 && rays[i].x >= 0
		&& rays[i].y < data()->map.height
		&& rays[i].x < data()->map.width)
	{
		player.x = rays[i].x * GRID_SIZE;
		player.y = rays[i].y * GRID_SIZE;
		ray.x = data()->player.x * GRID_SIZE;
		ray.y = data()->player.y * GRID_SIZE;
		draw_line_a_to_b(img, ray, player, RAY_COLOR);
	}
}

void	rays_draw_to_image(void)
{
	int		i;
	t_data	*datas;
	t_img	*img;
	t_point	player;
	t_point	ray;

	datas = data();
	img = &datas->imgs[RAYS_IMG];
	if (LINUX)
		img->ptr = my_new_image(data()->mlx, data()->minimap.width,
				data()->minimap.height, img);
	else
		img = image_clone(data()->mlx, &data()->imgs[MINIMAP_IMG], img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
			static_draw_single_ray(img, player, ray, i);
		i++;
	}
}

static void	ray_fill_struct(float angle, int i)
{
	float	delta;
	t_ray	*ray;
	t_frame	*window;

	ray = data()->rays;
	window = &data()->window;
	ray[i] = static_ray_get(angle);
	ray[i].index = i;
	delta = radian_limits(data()->player.angle - ray[i].angle);
	ray[i].dist = ray[i].len * cos(delta);
	ray[i].line_h = (window->height / ray[i].dist) * window->width
		/ window->height * ANGLE_OF_VIEW_CONST / ANGLE_OF_VIEW
		* WALL_HEIGHT_RATIO;
}

void	rays_create(void)
{
	int		i;
	float	angle;

	angle = radian_limits(data()->player.angle - ANGLE_OF_VIEW / 2 * DR);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		ray_fill_struct(angle, i);
		angle = radian_limits(angle + ANGLE_OF_VIEW * DR / NUMBER_OF_RAYS);
		i++;
	}
}
