#include "cub3d.h"

static void	static_images_create_environment_img(void)
{
	t_img	*img;

	img = &data()->imgs[ENV_IMG];
	img->ptr = my_new_image(data()->mlx, data()->window.width,
			data()->window.height, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
}

static void	static_images_create_player_img(void)
{
	t_img	*img;

	img = &data()->imgs[PLAYER_IMG];
	img->ptr = my_new_image(data()->mlx,
			MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	image_fill(img, MINIMAP_PLAYER_COLOR);
}

static void	static_images_create_minimap_img(void)
{
	t_img	*img;

	img = &data()->imgs[MINIMAP_IMG];
	img->ptr = my_new_image(data()->mlx, MINIMAP_RADIUS * 2 * MAP_GRID_SIZE,
			MINIMAP_RADIUS * 2 * MAP_GRID_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
}

void	images_create(void)
{
	static_images_create_player_img();
	static_images_create_environment_img();
	static_images_create_minimap_img();
}
