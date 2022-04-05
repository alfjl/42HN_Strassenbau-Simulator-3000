# include "cub3d.h"

static void	static_display_player()
{
	t_img	img;
	t_point	a;
	t_point	b;

	a.x = data()->player.x;
	a.y = data()->player.y;
	b.x = data()->player.x + data()->player.dx * NOSE;
	b.y = data()->player.y + data()->player.dy * NOSE;

	img.ptr = mlx_new_image(data()->mlx, data()->window.width, data()->window.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_line_a_to_b(&img, a, b, RED);
	
	mlx_put_image_to_window(data()->mlx, data()->win, img.ptr, 0, 0);
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[PLAYER_IMG].ptr, data()->player.x - PLAYER_SIZE / 2, data()->player.y - PLAYER_SIZE / 2);
	mlx_destroy_image(data()->mlx, img.ptr);
}

int	minimap(void)
{
	mlx_put_image_to_window(data()->mlx, data()->win, data()->imgs[MINIMAP_IMG].ptr, 0, 0);
	static_display_player();
	return (EXIT_SUCCESS);
}
