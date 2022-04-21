#include "cub3d.h"

static void	static_draw_wallsegment(int index, t_img *img)
{
	t_point	start;
	t_point	end;
	float	line_h;

	line_h = data()->rays[index].line_h;
	start.y = -line_h / 2 + data()->window.height / 2;
	data()->rays[index].tyoffset = 0;
	if (start.y < 0)
	{
		data()->rays[index].tyoffset = fabs((float)start.y)
		/ line_h * TEXTURE_SIZE;
		start.y = 0;
	}
	end.y = line_h / 2 + data()->window.height / 2;
	if (end.y >= data()->window.height)
		end.y = data()->window.height - 1;
	draw_vertical_line(img, start, end, index);
}

void	walls_draw_to_image(void)
{
	int		i;
	t_img	*img;

	img = &data()->imgs[WALLS_IMG];
	img->ptr = my_new_image(data()->mlx, data()->window.width,
			data()->window.height, img);
	if (img->ptr == NULL)
		exit_program(MLX_IMAGE);
	i = 0;
	while (i < NUMBER_OF_RAYS)
	{
		static_draw_wallsegment(i, img);
		i++;
	}
}
