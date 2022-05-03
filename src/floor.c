#include "cub3d.h"

int	get_sky_color(t_img *img, t_ray *ray, int y)
{
	int	color;
	int	tx;
	int	ty;
	int	image;

	(void)img;
	image = SKY_IMG;
	color = YELLOW;
	tx = ray->angle * (data()->imgs[image].width / (2 * M_PI));
	ty = y + data()->imgs[image].height / 4 - data()->player.dz;
	if (is_inside_image_limits(tx, ty, &data()->imgs[image]))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		// my_pixel_put(img, ray->screen_x, y, color);
	}
	return (color);
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

static int	static_get_texture_color(t_img *img, int image, t_ray *ray, int y)
{
	int	tx;
	int	ty;
	int	color;

	color = MAGENTA;
	tx = static_get_texture_value(data()->player.x,
			ray->x, y, ray->dist);
	ty = static_get_texture_value(data()->player.y,
			ray->y, y, ray->dist);
	if (is_inside_image_limits(tx, ty, img))
	{
		color = *(unsigned int *)(data()->imgs[image].addr
				+ (unsigned int)((int)ty * data()->imgs[image].line_len
					+ tx * (data()->imgs[image].bits_per_pixel / 8))) + ALPHA;
		// my_pixel_put(img, ray->screen_x, y, color);
	}
	return (color);
}

int	get_ceiling_color(t_img *img, t_ray *ray, int y)
{
	if (SKY_ENABLED)
		return (get_sky_color(img, ray, y));
	else if (!CEILING_TEXTURE_ENABLED)
		return (data()->map.ceiling.rgb);
	return (static_get_texture_color(img, CEILING_IMG, ray, y));
}

int	get_floor_color(t_img *img, t_ray *ray, int y)
{
	if (!FLOOR_TEXTURE_ENABLED)
		return (data()->map.floor.rgb);
	return (static_get_texture_color(img, FLOOR_IMG, ray, y));
}
