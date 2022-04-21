#include "cub3d.h"

static void	static_new_minimap(t_img *dst)
{
	t_point	dst_p;
	int		color;
	float	map_x;
	float	map_y;

	map_y = (data()->player.y - MINIMAP_RADIUS);
	dst_p.y = 0;
	while (dst_p.y < dst->height)
	{
		dst_p.x = 0;
		map_x = (data()->player.x - MINIMAP_RADIUS);
		while (dst_p.x < dst->width)
		{
			color = MINIMAP_BACKGROUND_COLOR;
			if (map_y < data()->map.height && map_y >= 0 && map_x < data()->map.width
		&& map_x >= 0) //is inside map function
			{
				if (data()->map.grid[(int)map_y][(int)map_x] == WALL)
					color = MINIMAP_WALL_COLOR;
				else
					color = MINIMAP_SPACE_COLOR;
				if ((map_y > (int)map_y - EPSILON && map_y < (int)map_y + EPSILON) || (map_x > (int)map_x - EPSILON && map_x < (int)map_x + EPSILON))
					color = MINIMAP_GRID_COLOR;
			}
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
	rays_draw_to_image();
}
