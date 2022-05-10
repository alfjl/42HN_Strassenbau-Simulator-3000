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

int	textures_determine_color(t_img *img, int x, int y, int size)
{
	int		color;
	float	scale_x;
	float	scale_y;
	float	tx;
	float	ty;

	scale_x = img->width / (float)size;
	scale_y = img->height / (float)size;
	tx = x * scale_x;
	ty = y * scale_y;
	color = get_pixel_color(img, tx, ty) - ALPHA;
	return (color);
}

void	textures_resize_img(void* mlx, t_img *tmp, t_img *img, int size)
{
	int		y;
	int		x;
	int		color;

	img->ptr = my_new_image(mlx, size,
			size, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = textures_determine_color(tmp, x, y, size);
			my_pixel_put(img, x, y, color);
			x++;
		}	
		y++;
	}
}

static void	static_create_img_from_texture(void* mlx, int image, float brightness)
{
	t_img	*tmp;
	t_img	*img;

	tmp = &data()->imgs[TMP_IMG];
	img = &data()->imgs[image];
	tmp->ptr = my_xpm_file_to_image(mlx, img->path, tmp);
	if (tmp->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	textures_resize_img(mlx, tmp, img, TEXTURE_SIZE);
	my_destroy_image(mlx, tmp);
	if (SHADING_ENABLED)
		static_textures_shade_image(img, brightness);
}

void	textures_convert_to_image(void* mlx)
{
	t_img	*img;

	img = &data()->imgs[SKY_IMG];
	static_create_img_from_texture(mlx, NORTH_IMG, SHADE_NORTH);
	static_create_img_from_texture(mlx, SOUTH_IMG, SHADE_SOUTH);
	static_create_img_from_texture(mlx, EAST_IMG, SHADE_EAST);
	static_create_img_from_texture(mlx, WEST_IMG, SHADE_WEST);
	if (FLOOR_TEXTURE_ENABLED)
		static_create_img_from_texture(mlx, FLOOR_IMG, SHADE_FLOOR);
	if (CEILING_TEXTURE_ENABLED)
		static_create_img_from_texture(mlx, CEILING_IMG, SHADE_CEILING);
	if (SKY_ENABLED)
	{
		img->ptr = my_xpm_file_to_image(mlx, img->path, img);
		if (img->ptr == NULL)
			exit_end_program_error(MLX_IMAGE);
	}
}
