#include "cub3d.h"

void	my_destroy_image(void *mlx_ptr, t_img *img)
{
	if (img->ptr != NULL)
		mlx_destroy_image(mlx_ptr, img->ptr);
	img->ptr = NULL;
}

void	*my_new_image(void *mlx_ptr, int width, int height, t_img *img)
{
	if (LINUX && HAS_ALPHA)
		img->ptr = mlx_new_image_alpha(mlx_ptr, width, height);
	else
		img->ptr = mlx_new_image(mlx_ptr, width, height);
	if (img->ptr == NULL)
		return (NULL);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	img->width = width;
	img->height = height;
	if (!HAS_ALPHA)
		image_fill(img, TRANSPARENT);
	return (img->ptr);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!is_inside_limits(x, y, img))
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
