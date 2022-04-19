#include "cub3d.h"

static void	static_shade_image(t_img *img, float brightness)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = *(unsigned int *)(img->addr
				+ (unsigned int)((int)y * img->line_length
					+ x * (img->bits_per_pixel / 8)));
			color = argb_color_shade(color, brightness);
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

static void	static_create_img_from_texture(int image, float brightness)
{
	t_img	*img;

	img = &data()->imgs[image];
	img->ptr = mlx_xpm_file_to_image(data()->mlx, img->path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->width = TEXTURE_SIZE;
	img->height = TEXTURE_SIZE;
	static_shade_image(img, brightness);
}

void	textures_load(void)
{
	static_create_img_from_texture(SOUTH_IMG, 0.5);
	static_create_img_from_texture(NORTH_IMG, 1.0);
	static_create_img_from_texture(EAST_IMG, 0.75);
	static_create_img_from_texture(WEST_IMG, 0.75);
}
