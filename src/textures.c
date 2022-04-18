#include "cub3d.h"

static void	static_create_img_from_texture(int image)
{
	t_img	*img;

	img = &data()->imgs[image];
	img->ptr = mlx_xpm_file_to_image(data()->mlx, img->path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = TEXTURE_SIZE;
	img->height = TEXTURE_SIZE;
}

void	textures_load(void)
{
	static_create_img_from_texture(SOUTH_IMG);
	static_create_img_from_texture(NORTH_IMG);
	static_create_img_from_texture(EAST_IMG);
	static_create_img_from_texture(WEST_IMG);
}
