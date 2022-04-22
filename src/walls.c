#include "cub3d.h"

static bool	static_is_door(float y, float x)
{
	if (y < data()->map.height && y >= 0 && x < data()->map.width
		&& x >= 0)
	{
		if (data()->map.grid[(int)y][(int)x] == WALL)
			return (true);
	}
	return (false);
}

void	wall_open_door(void)
{
	float	x;
	float	y;
	t_ray	*ray;
	
	ray = &data()->rays[(NUMBER_OF_RAYS - 1) / 2];
	x = ray->x;
	y = ray->y;
	if (ray->orientation == NORTH)
		y -= EDGE;
	if (ray->orientation == WEST)
		x -= EDGE;
	if (ray->len > 1)
		return ;
	if (static_is_door(y, x))
		data()->map.grid[(int)y][(int)x] = SPACE;
}

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
