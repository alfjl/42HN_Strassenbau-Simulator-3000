#include "cub3d.h"

static void	static_draw_single_ray(t_img *img, int i)
{
	t_ray		*rays;
	t_point		player_p;
	t_point		ray_p;
	t_player	*player;

	rays = data()->rays;
	player = &data()->player;
	ray_p.x = (rays[i].mini_x - player->x + MINIMAP_RADIUS) * GRID_SIZE;
	ray_p.y = (rays[i].mini_y - player->y + MINIMAP_RADIUS) * GRID_SIZE;
	player_p.x = MINIMAP_RADIUS * GRID_SIZE;
	player_p.y = MINIMAP_RADIUS * GRID_SIZE;
	draw_line_a_to_b(img, player_p, ray_p, RAY_COLOR);
}

void	rays_draw_to_image(void)
{
	int		i;
	t_data	*datas;
	t_img	*img;

	datas = data();
	img = &datas->imgs[MINIMAP_IMG];
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
			static_draw_single_ray(img, i);
		i++;
	}
}