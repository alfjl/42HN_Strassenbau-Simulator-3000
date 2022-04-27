#include "cub3d.h"

static void	static_images_create_background_img(void)
{
	int		x;
	int		y;
	t_img	*img;

	img = &data()->imgs[BACKGROUND_IMG];
	img->ptr = my_new_image(data()->mlx, data()->window.width,
			data()->window.height, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	y = 0;
	while (y < data()->window.height)
	{
		x = 0;
		while (x < data()->window.width)
		{
			if (y < data()->window.height / 2)
				my_pixel_put(img, x, y, data()->map.ceiling.rgb);
			else
				my_pixel_put(img, x, y, data()->map.floor.rgb);
			x++;
		}
		y++;
	}
}

static void	static_images_create_player_img(void)
{
	int		x;
	int		y;
	t_img	*img;

	img = &data()->imgs[PLAYER_IMG];
	img->ptr = my_new_image(data()->mlx,
			MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	y = 0;
	while (y < MINIMAP_PLAYER_SIZE)
	{
		x = 0;
		while (x < MINIMAP_PLAYER_SIZE)
		{
			my_pixel_put(img, x, y, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

void	images_create(void)
{
	if (HAS_ALPHA)
		static_images_create_background_img();
	static_images_create_player_img();
}
