#include "cub3d.h"

static void	static_copy_img_section(t_img *src)
{
	t_img	*img;
	int		img_x;
	int		img_y;
	int		src_x;
	int		src_y;
	int		color;

	img = &data()->imgs[MICROMAP_IMG];
	src_y = (data()->player.y - MICROMAP_RADIUS) * GRID_SIZE;
	src_x = (data()->player.x - MICROMAP_RADIUS) * GRID_SIZE;
	img_y = 0;
	while (img_y < img->height)
	{
		img_x = 0;
		while (img_x < img->width)
		{
			color = MINIMAP_BACKGROUND_COLOR;
			if (!pixel_is_outside_img_limits(src_x + img_x, src_y + img_y, src))
			{
				color = *(unsigned int *)(src->addr
					+ (unsigned int)((int)(src_y + img_y) * src->line_length
						+ (src_x + img_x) * src->bits_per_pixel / 8));
				// if (color != TRANSPARENT)
				// 	my_pixel_put(img, img_x, img_y, color);
			}
			if (color != TRANSPARENT)
				my_pixel_put(img, img_x, img_y, color);
			img_x++;
		}
		img_y++;
	}
}

void	micromap_draw_to_image(void)
{
	t_img	*img;

	img = &data()->imgs[MICROMAP_IMG];
	img->ptr = my_new_image(data()->mlx, MICROMAP_RADIUS * 2 * GRID_SIZE, MICROMAP_RADIUS * 2 * GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	static_copy_img_section(&data()->imgs[MINIMAP_IMG]);
	static_copy_img_section(&data()->imgs[RAYS_IMG]);
}
