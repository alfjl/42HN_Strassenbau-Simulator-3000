#include "cub3d.h"

static void	static_walls_draw_wallsegment(t_data *data, t_ray *ray, t_img *img)
{
	(void)img;
	float	line_h;

	line_h = ray->line_h;
	ray->start_y = -line_h / 2 + data->window.height / 2 + data->player.dz;
	ray->tyoffset = 0;
	if (ray->start_y < 0)
	{
		ray->tyoffset = fabs((float)ray->start_y)
		/ line_h * TEXTURE_SIZE;
		ray->start_y = 0;
	}
	ray->end_y = line_h / 2 + data->window.height / 2 + data->player.dz;
	if (ray->end_y >= data->window.height)
		ray->end_y = data->window.height - 1;
}

void	walls_draw_to_image(void)
{
	int		i;
	t_img	*img;
	t_data	*datas;

	datas = data();
	img = &datas->imgs[WALLS_IMG];
	img->ptr = my_new_image(datas->mlx, datas->window.width,
			datas->window.height, img);
	if (img->ptr == NULL)
		exit_end_program_error(MLX_IMAGE);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_walls_draw_wallsegment(datas, &datas->rays[i], img);
		walls_draw_vertical_line(datas, img, &datas->rays[i]);
		i++;
	}
}
