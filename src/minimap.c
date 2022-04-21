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

static void	static_rays_draw_to_image(t_img *img)
{
	int		i;

	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
			static_draw_single_ray(img, i);
		i++;
	}
}

static int	static_determine_color(float map_y, float map_x)
{
	int		color;
	t_map	*map;

	map = &data()->map;
	color = MINIMAP_BACKGROUND_COLOR;
	if (map_y < map->height && map_y >= 0
		&& map_x < map->width && map_x >= 0)
	{
		if (map->grid[(int)map_y][(int)map_x] == WALL)
			color = MINIMAP_WALL_COLOR;
		else
			color = MINIMAP_SPACE_COLOR;
		if ((map_y > (int)map_y - EPSILON && map_y < (int)map_y + EPSILON)
			|| (map_x > (int)map_x - EPSILON && map_x < (int)map_x + EPSILON))
			color = MINIMAP_GRID_COLOR;
	}
	return (color);
}

static void	static_new_minimap(t_img *dst)
{
	t_point		dst_p;
	int			color;
	float		map_x;
	float		map_y;
	t_player	*player;

	player = &data()->player;
	map_y = (player->y - MINIMAP_RADIUS);
	dst_p.y = 0;
	while (dst_p.y < dst->height)
	{
		dst_p.x = 0;
		map_x = (player->x - MINIMAP_RADIUS);
		while (dst_p.x < dst->width)
		{
			color = static_determine_color(map_y, map_x);
			my_pixel_put(dst, dst_p.x, dst_p.y, color);
			dst_p.x++;
			map_x = map_x + 1.0 / GRID_SIZE;
		}
		dst_p.y++;
		map_y = map_y + 1.0 / GRID_SIZE;
	}
}

void	minimap_draw_to_image(void)
{
	t_img	*img;

	img = &data()->imgs[MINIMAP_IMG];
	img->ptr = my_new_image(data()->mlx, MINIMAP_RADIUS * 2 * GRID_SIZE,
			MINIMAP_RADIUS * 2 * GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	static_new_minimap(img);
	static_rays_draw_to_image(img);
}
