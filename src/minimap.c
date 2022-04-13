#include "cub3d.h"

void	player_nose_draw_to_image(void)
{
	t_point	a;
	t_point	b;
	t_img	*img;
	img = &data()->imgs[NOSE_IMG];

	a.x = data()->player.x * GRID_SIZE;
	a.y = data()->player.y * GRID_SIZE;
	b.x = data()->player.x * GRID_SIZE + data()->player.dx * NOSE;
	b.y = data()->player.y * GRID_SIZE + data()->player.dy * NOSE;
	img->ptr = mlx_new_image_alpha(data()->mlx, data()->minimap.width, data()->minimap.height);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (b.y < 0 ||  b.x < 0) //better check
		return;
	draw_line_a_to_b(img, a, b, BLACK);
}
