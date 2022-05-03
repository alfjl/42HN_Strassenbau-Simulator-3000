#include "cub3d.h"

int	get_sky_color(t_ray *ray, int y)
{
	int	tx;
	int	ty;

	tx = ray->angle * (data()->imgs[SKY_IMG].width / (2 * M_PI));
	ty = y + data()->imgs[SKY_IMG].height / 4 - data()->player.dz;
	return (get_pixel_color(&data()->imgs[SKY_IMG], tx, ty));
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

static int	static_get_texture_color(int image, t_ray *ray, int y)
{
	int	tx;
	int	ty;

	tx = static_get_texture_value(data()->player.x,
			ray->x, y, ray->dist);
	ty = static_get_texture_value(data()->player.y,
			ray->y, y, ray->dist);
	return (get_pixel_color(&data()->imgs[image], tx, ty));
}

int	get_ceiling_color(t_ray *ray, int y)
{
	if (SKY_ENABLED)
		return (get_sky_color(ray, y));
	else if (!CEILING_TEXTURE_ENABLED)
		return (data()->map.ceiling.rgb);
	return (static_get_texture_color(CEILING_IMG, ray, y));
}

int	get_floor_color(t_ray *ray, int y)
{
	if (!FLOOR_TEXTURE_ENABLED)
		return (data()->map.floor.rgb);
	return (static_get_texture_color(FLOOR_IMG, ray, y));
}
