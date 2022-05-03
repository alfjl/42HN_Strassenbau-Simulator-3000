#include "cub3d.h"

static void	static_textures_shade_image(t_img *img, float brightness)
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
			color = get_pixel_color(img, x, y);
			color = argb_shade_color(color, brightness);
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

static int	static_textures_determine_color(t_img *img, int x, int y)
{
	int		color;
	float	scale_x;
	float	scale_y;
	float	tx;
	float	ty;

	scale_x = img->width / (float)TEXTURE_SIZE;
	scale_y = img->height / (float)TEXTURE_SIZE;
	tx = x * scale_x;
	ty = y * scale_y;
	color = get_pixel_color(img, tx, ty);
	return (color);
}

static void	static_textures_resize_img(t_img *tmp, t_img *img)
{
	int		y;
	int		x;
	int		color;

	img->ptr = my_new_image(data()->mlx, TEXTURE_SIZE,
			TEXTURE_SIZE, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = static_textures_determine_color(tmp, x, y);
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

static void	static_create_img_from_texture(int image, float brightness)
{
	t_img	*tmp;
	t_img	*img;

	tmp = &data()->imgs[TMP_IMG];
	img = &data()->imgs[image];
	tmp->ptr = my_xpm_file_to_image(data()->mlx, img->path, tmp);
	if (tmp->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	static_textures_resize_img(tmp, img);
	my_destroy_image(data()->mlx, tmp);
	if (SHADING_ENABLED)
		static_textures_shade_image(img, brightness);
}

void	textures_load(void)
{
	t_img	*img;

	img = &data()->imgs[SKY_IMG];
	static_create_img_from_texture(NORTH_IMG, SHADE_NORTH);
	static_create_img_from_texture(SOUTH_IMG, SHADE_SOUTH);
	static_create_img_from_texture(EAST_IMG, SHADE_EAST);
	static_create_img_from_texture(WEST_IMG, SHADE_WEST);
	if (FLOOR_TEXTURE_ENABLED)
		static_create_img_from_texture(FLOOR_IMG, SHADE_FLOOR);
	if (CEILING_TEXTURE_ENABLED)
		static_create_img_from_texture(CEILING_IMG, SHADE_CEILING);
	if (SKY_ENABLED)
	{
		img->ptr = my_xpm_file_to_image(data()->mlx, img->path, img);
		if (img->ptr == NULL)
			exit_end_program_error(MLX_IMAGE);
	}
}
