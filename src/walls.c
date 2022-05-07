#include "cub3d.h"

static void	static_walls_calculate_limits(t_data *data, t_ray *ray)
{
	float	line_h;

	line_h = ray->line_h;
	ray->start_y = -line_h / 2 + data->window.height / 2 + data->player.dz;
	ray->tyoffset = 0;
	if (ray->start_y < 0)
	{
		ray->tyoffset = fabs((float)ray->start_y) / line_h * TEXTURE_SIZE;
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
	img = &datas->imgs[ENV_IMG];
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_walls_calculate_limits(datas, &datas->rays[i]);
		walls_draw_segment(datas, img, &datas->rays[i]);
		i++;
	}
}
