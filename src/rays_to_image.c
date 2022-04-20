#include "cub3d.h"

static void	static_draw_single_ray(t_img *img, t_point player_p, t_point ray_p,
	int i)
{
	t_ray		*rays;
	t_map		*map;
	t_player	*player;

	rays = data()->rays;
	map = &data()->map;
	player = &data()->player;
	if (rays[i].y >= 0 && rays[i].x >= 0
		&& rays[i].y < map->height
		&& rays[i].x < map->width)
	{
		player_p.x = rays[i].x * GRID_SIZE;
		player_p.y = rays[i].y * GRID_SIZE;
		ray_p.x = player->x * GRID_SIZE;
		ray_p.y = player->y * GRID_SIZE;
		draw_line_a_to_b(img, ray_p, player_p, RAY_COLOR);
	}
}

void	rays_draw_to_image(void)
{
	int		i;
	t_data	*datas;
	t_img	*img;
	t_point	player_p;
	t_point	ray_p;

	datas = data();
	img = &datas->imgs[RAYS_IMG];
	if (LINUX)
		img->ptr = my_new_image(datas->mlx, datas->minimap.width,
				datas->minimap.height, img);
	else
		img = image_clone(datas->mlx, &datas->imgs[MINIMAP_IMG], img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
			static_draw_single_ray(img, player_p, ray_p, i);
		i++;
	}
}