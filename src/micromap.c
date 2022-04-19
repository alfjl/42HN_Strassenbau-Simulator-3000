#include "cub3d.h"

// static int	static_determine_color(t_img *src, )
// {
// 	int	color;

// 	color = MINIMAP_BACKGROUND_COLOR;
// 	if (!is_out_of_limits(src_x + dst_x, src_y + dst_y, src))
// 	{
// 		color = *(unsigned int *)(src->addr
// 				+ (unsigned int)((int)(src_y + dst_y)*src->line_len
// 					+ (src_x + dst_x) * src->bits_per_pixel / 8));
// 	}
// 	return (color);
// }

static void	static_copy_img_section(t_img *src, t_img *dst)
{
	t_point	dst_p;
	t_point	src_p;
	int		color;

	src_p.y = (data()->player.y - MICROMAP_RADIUS) * GRID_SIZE;
	src_p.x = (data()->player.x - MICROMAP_RADIUS) * GRID_SIZE;
	dst_p.y = 0;
	while (dst_p.y < dst->height)
	{
		dst_p.x = 0;
		while (dst_p.x < dst->width)
		{
			color = MINIMAP_BACKGROUND_COLOR;
			if (!is_out_of_limits(src_p.x + dst_p.x, src_p.y + dst_p.y, src))
			{
				color = *(unsigned int *)(src->addr
						+ (unsigned int)((int)(src_p.y + dst_p.y)*src->line_len
							+ (src_p.x + dst_p.x) * src->bits_per_pixel / 8));
			}
			if (color != TRANSPARENT)
				my_pixel_put(dst, dst_p.x, dst_p.y, color);
			dst_p.x++;
		}
		dst_p.y++;
	}
}

void	micromap_draw_to_image(void)
{
	t_img	*img;

	img = &data()->imgs[MICROMAP_IMG];
	img->ptr = my_new_image(data()->mlx, MICROMAP_RADIUS * 2 * GRID_SIZE,
			MICROMAP_RADIUS * 2 * GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	static_copy_img_section(&data()->imgs[MINIMAP_IMG], img);
	static_copy_img_section(&data()->imgs[RAYS_IMG], img);
}
