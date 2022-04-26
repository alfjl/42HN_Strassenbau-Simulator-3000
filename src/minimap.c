#include "cub3d.h"

static void	static_minimap_draw_single_ray(t_img *img, int i)
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

static void	static_minimap_draw_rays(t_img *img)
{
	int		i;

	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		if (!(i % MINIMAP_RAY_DENSITY_FACTOR))
			static_minimap_draw_single_ray(img, i);
		i++;
	}
}

static int	static_minimap_determine_color(float map_y, float map_x)
{
	int		color;
	t_map	*map;
	float	epsilon;

	epsilon = (1.0 / GRID_SIZE);
	map = &data()->map;
	color = MINIMAP_BACKGROUND_COLOR;
	if (map_y < map->height && map_y >= 0
		&& map_x < map->width && map_x >= 0)
	{
		if (map->grid[(int)(map_y - epsilon)][(int)(map_x - epsilon)] == WALL)
			color = MINIMAP_WALL_COLOR;
		else
			color = TRANSPARENT;
		if (!MINIMAP_GRID_ENABLED)
			return (color);
		if ((map_y > (int)map_y - epsilon && map_y < (int)map_y + epsilon)
			|| (map_x > (int)map_x - epsilon && map_x < (int)map_x + epsilon))
			color = MINIMAP_GRID_COLOR;
	}
	return (color);
}

static void	static_minimap_draw_map(t_img *dst)
{
	t_point		dst_p;
	int			color;
	float		map_x;
	float		map_y;
	float		epsilon;

	epsilon = (1.0 / GRID_SIZE);
	map_y = (data()->player.y - MINIMAP_RADIUS) + epsilon;
	dst_p.y = 0;
	while (dst_p.y < dst->height)
	{
		dst_p.x = 0;
		map_x = (data()->player.x - MINIMAP_RADIUS) + epsilon;
		while (dst_p.x < dst->width)
		{
			color = static_minimap_determine_color(map_y, map_x);
			if (color != (int)TRANSPARENT)
				my_pixel_put(dst, dst_p.x, dst_p.y, color);
			dst_p.x++;
			map_x = map_x + epsilon;
		}
		dst_p.y++;
		map_y = map_y + epsilon;
	}
}

void	minimap_draw_to_image(void)
{
	t_img	*img;

	img = &data()->imgs[MINIMAP_IMG];
	img->ptr = my_new_image(data()->mlx, MINIMAP_RADIUS * 2 * GRID_SIZE,
			MINIMAP_RADIUS * 2 * GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	image_fill(img, MINIMAP_SPACE_COLOR);
	static_minimap_draw_rays(img);
	static_minimap_draw_map(img);
}
