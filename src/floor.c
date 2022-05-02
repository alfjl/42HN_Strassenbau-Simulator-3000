#include "cub3d.h"

void	get_sky_color(t_img *img, t_point start, t_ray *ray, int y)
{
	int	color;
	int	tx;
	int	ty;
	int	image;

	image = SKY_IMG;
	tx = ray->angle * (data()->imgs[image].width / (2 * M_PI));
	ty = y + data()->imgs[image].height / 4 - data()->player.dz;
	if (is_inside_image_limits(tx, ty, &data()->imgs[image]))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

static int	static_get_texture_value(float player_value,
	float ray_value, int y, float wall_dist)
{
	float	current_dist;
	float	weight;
	float	current_floor_value;

	current_dist = fabs(data()->window.height / (2.0 * (y - data()->player.dz)
				- data()->window.height));
	weight = current_dist / wall_dist;
	current_floor_value = weight * (ray_value - player_value)
		+ player_value / 2;
	return ((current_floor_value - (int)current_floor_value) * TEXTURE_SIZE);
}

static	void	static_test(int image, t_point start, t_ray *ray, int y)
{
	int	tx;
	int	ty;
	int	color;
	t_img *img;

	img = &data()->imgs[WALLS_IMG];
	tx = static_get_texture_value(data()->player.x,
			ray->x, y, ray->dist);
	ty = static_get_texture_value(data()->player.y,
			ray->y, y, ray->dist);
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		my_pixel_put(img, start.x, y, color);
	}
}

void	get_ceiling_color(t_img *img, t_point start, t_ray *ray, int y)
{
	if (SKY_ENABLED)
	{
		get_sky_color(img, start, ray, y);
		return ;
	}
	else if (!CEILING_TEXTURE_ENABLED)
	{
		my_pixel_put(img, start.x, y, data()->map.ceiling.rgb);
		return ;
	}
	static_test(CEILING_IMG, start, ray, y);
}

void	get_floor_color(t_img *img, t_point start, t_ray *ray, int y)
{
	if (!FLOOR_TEXTURE_ENABLED)
	{
		my_pixel_put(img, start.x, y, data()->map.floor.rgb);
		return ;
	}
	static_test(FLOOR_IMG, start, ray, y);
}
